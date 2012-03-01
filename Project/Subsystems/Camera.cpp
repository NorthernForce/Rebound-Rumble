#include <vxWorks.h>
#include <usrLib.h>
#include <limits>
#include "Camera.h"
#include "../Robotmap.h"
#include "Vision/BinaryImage.h"

/** Private NI function needed to write to the VxWorks target */
IMAQ_FUNC int Priv_SetWriteFileAllowed(UINT32 enable); 

/**
 * @brief Creates the camera object.
 *
 * By specifying the IP address of the camera we initialize without the
 * driver station being present
 *
 */
Camera::Camera() :
	Subsystem("Camera"),
	m_cam (AxisCamera::GetInstance("10.1.72.11")),
	m_imageProcessingTask ("ImageProcessing", (FUNCPTR)Camera::ImageProcessingTask, Task::kDefaultPriority + 10),
	m_cameraSemaphore (semBCreate (SEM_Q_PRIORITY, SEM_FULL)),
	m_saveSourceImage (false),
	m_saveProcessedImages (false),
	m_frameProcessingTime (0)
{
	SetDirectory ("/tmp/Images");
	m_imageProcessingTask.Start (reinterpret_cast<UINT32> (this));
}

/** @brief Destroys the camera object.
 *
 * @author Stephen Nutt
 */
Camera::~Camera()
{
	semDelete (m_cameraSemaphore);
}

void Camera::InitDefaultCommand()
{
}

/**
 * @brief Initialize the camera and the tracking
 * code to do the tracking, set all
 * variables, and connect to the driver
 * station to display images.
 */
void Camera::InitCamera()
{
}

/**
 * @brief Returns the distance to the target.
 * @return float Distance, in feet.
 */
float Camera::GetDistanceToTarget() const
{
	Rect topTarget;
	topTarget.top = INT_MAX;
	
	// We need to lock m_cameraSemaphore to protect access
	// to m_particles
	{
		const Synchronized sync (m_cameraSemaphore);
		if (m_particles.empty())
		{
			return std::numeric_limits<float>::quiet_NaN();
		}

		for (size_t i = 0; i < m_particles.size(); ++i)
		{
			const Rect& r = m_particles[i].boundingRect;
			if (r.top < topTarget.top)
			{
				topTarget = r;
			}
		}
	}
	
	//Calculate the distance to the target.
	int width;
	int height;
	switch (m_cam.GetResolution())
	{
		case AxisCameraParams::kResolution_160x120:
		default:
			width = 160;
			height = 120;
			break;

		case AxisCameraParams::kResolution_320x240:
			width = 320;
			height = 240;
			break;
			
		case AxisCameraParams::kResolution_640x480:
			width = 640;
			height = 480;
			break;
			
		case AxisCameraParams::kResolution_640x360:
			width = 640;
			height = 360;
			break;
	}

	const double c = 0.292659195508492; // tan(32.625/2)
	const double b = 0.398959545973719; // tan(43.5/2)
	const double h = 1.5 * height / 2 * c * topTarget.height;
	const double w = 2 * height / 2 * b * topTarget.width;
	return (h + w) / 2;
}

float Camera::GetHorizontalDistance() const
{
    float distance = GetDistanceToTarget();
    if (distance == std::numeric_limits<float>::quiet_NaN()) return distance;
    return distance*cos(asin(k_targetHeight/distance));
}

/** @brief Returns true if there is a target that we can shoot at.
 *
 * @author Stephen Nutt
 */
bool Camera::HasTarget() const
{
	const Synchronized sync (m_cameraSemaphore);
	if(!m_particles.empty())
    {
       return true;
		/**/
    } 
    return false;
}

bool Camera::HasValidTarget()
{
	float x = GetHorizontalDistance();
	if ( (x == std::numeric_limits<float>::quiet_NaN()) || (x > k_maxDistance)) return false;
	else return true;
}

/**
 * @brief Gets the number of targets the camera can see
 * @return The number of targets the camera can see
 */
int Camera::GetNumberOfTargets() const
{
	const Synchronized sync (m_cameraSemaphore);
	return m_particles.size();
}

/**
 * @brief Gets the apparent angle that the robot lies
 * on relative to a line perpendicular to the targets.
 *
 * The simple approach taken is to look for the highest
 * target - this may be either the center target or the
 * closest target, both of which are suitable candidates
 * to target in on.
 *
 * @return A float, the angle in radians of deviation.
 */
float Camera::GetAngleToTarget() const
{
	Rect topTarget;
	topTarget.top = INT_MAX;

	// We need to lock m_cameraSemaphore to protect access
	// to m_particles
	{
		const Synchronized sync (m_cameraSemaphore);
		if (m_particles.empty())
		{
			return std::numeric_limits<float>::quiet_NaN();
		}

		for (size_t i = 0; i < m_particles.size(); ++i)
		{
			const Rect& r = m_particles[i].boundingRect;
			if (r.top < topTarget.top)
			{
				topTarget = r;
			}
		}
	}

	// Calculate an approximate angle to the target
	// This is very imprecise, but the precision does
	// not matter as when we are aligned on the target
	// the target will be in the center of the camera
	// image, and that is what matters.
	int center = topTarget.left + topTarget.width / 2;
	switch (m_cam.GetResolution())
	{
		case AxisCameraParams::kResolution_160x120:
			return (center - 80) / 4 * M_PI / 180;

		case AxisCameraParams::kResolution_320x240:
			return (center - 160) / 8 * M_PI / 180;

		case AxisCameraParams::kResolution_640x480:
		case AxisCameraParams::kResolution_640x360:
		default:
			return (center - 320) / 16 * M_PI / 180;
	}
}

/** @brief Sets the directory within which to write the camera images
 *
 * @author Stephen Nutt
 */
void Camera::SetDirectory (
	const char* directory,
	unsigned nextImage)
{
	const Synchronized sync (m_cameraSemaphore);
	strcpy (m_directory, directory);
	Priv_SetWriteFileAllowed(1);
//	mkdir (m_directory); Does this work??
	m_lastImageNo = m_imageNo = nextImage - 1;
}

/** @brief Captures the next n images from the camera
 *
 * @author Stephen Nutt
 */
void Camera::CaptureImages (unsigned count)
{
	const Synchronized sync (m_cameraSemaphore);
	m_lastImageNo = std::min (m_imageNo + count, m_lastImageNo + count);
}

/** @brief Static function called when the camera task is started,
 * used to start the ProcessImages function
 *
 */
void Camera::ImageProcessingTask(Camera& camera)
{
	camera.ProcessImages();
}

/** @brief Process the camera images and determines the number and
 * position of any targets within the camera frame
 *
 */
void Camera::ProcessImages()
{
	// Wait for the camera to initialize
	Wait(2.0);
	printf("Setting camera parameters\n");
	m_cam.WriteResolution(AxisCamera::kResolution_320x240);
	m_cam.WriteCompression(20);
	m_cam.WriteBrightness(50);
    m_cam.WriteMaxFPS(8);
	printf("Camera parameters set./n");

	UINT32 frameStart = GetFPGATime();
	while (true)
	{
		// Wait for a new image to be available
		if (m_cam.IsFreshImage() == false)
		{
			taskDelay (2);
			continue;
		}

		bool saveSourceImage = false;
		bool saveProcessedImages = false;
		if (m_imageNo < m_lastImageNo)
		{
			saveSourceImage = m_saveSourceImage;
			saveProcessedImages = m_saveProcessedImages;
			if (saveSourceImage || saveProcessedImages) ++m_imageNo;
		}

		m_cam.GetImage (&m_image);
		if (saveSourceImage ) SaveImage(m_image, "src.jpg");

		//@TODO correct HSL thresholds.
		Threshold violetThreshold (168, 205, 22, 255, 65, 255);
		const std::auto_ptr<BinaryImage> violetPixels (m_image.ThresholdHSL(violetThreshold));
		if (violetPixels.get() == 0) continue;
		if (saveProcessedImages) SaveImage (*violetPixels, "violet.png");

		const std::auto_ptr<BinaryImage> bigObjectsImage (violetPixels->RemoveSmallObjects (false, 2));
		if (bigObjectsImage.get() == 0) continue;
		if (saveProcessedImages) SaveImage (*bigObjectsImage, "big.png");

		const std::auto_ptr<BinaryImage> convexHullImage (bigObjectsImage->ConvexHull (false));
		if (convexHullImage.get() == 0) continue;
		if (saveProcessedImages) SaveImage (*convexHullImage, "hull.png");

		const int particleCount = convexHullImage->GetNumberParticles();

		// Save the particle analysis for use by the main thread.
		// We need to lock m_cameraSemaphore to protect access
		// to m_particles
		{
			const Synchronized sync (m_cameraSemaphore);
			m_particles.resize (particleCount);
			for (int i = 0; i < particleCount; ++i)
			{
				ParticleAnalysisReport& particle = m_particles[i];
				particle = convexHullImage->GetParticleAnalysisReport(i);
			}
		}

		// Update the processing time.  We add 1 to ensure the time
		// is never 0
		const UINT32 now = GetFPGATime();
		m_frameProcessingTime = (now - frameStart) + 1;
		frameStart = now;
	}
}

/** @brief Writes the image to the file system
 *
 * @author Stephen Nutt
 */
void Camera::SaveImage (
	ImageBase& image,
	const char* name) const
{
	char path[60];
	{
		const Synchronized sync (m_cameraSemaphore);
		sprintf (path, "%s/Img%04d_%s", m_directory, m_imageNo, name);
	}
	image.Write(path);
}
