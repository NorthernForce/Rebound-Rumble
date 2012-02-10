#include <vxWorks.h>
#include <usrLib.h>
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
	m_saveSourceImage (true),
	m_saveProcessedImages (true),
	m_frameProcessingTime (0)
{
	SetDirectory ("/tmp/Images");
	CaptureImages (20);
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
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
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
    return 0.0; // Not implemented yet
}

/**
 * @brief Makes the camera look around to find a
 * target. Used only if the target is lost.
 */
void Camera::Search()
{
}

/** @brief Returns true if at least one target has been
 * found.
 *
 * @author Stephen Nutt
 */
bool Camera::HasTarget() const
{
	const Synchronized sync (m_cameraSemaphore);
	return !m_particles.empty();
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
 * @return A float, the angle in degrees of deviation.
 */
float Camera::GetAngleToTarget() const
{
	Rect topTarget;
	topTarget.top = INT_MAX;

	// We need to lock m_cameraSemaphore to protect access
	// to m_particles
	{
		const Synchronized sync (m_cameraSemaphore);
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
			return (center - 80) / 4;

		case AxisCameraParams::kResolution_320x240:
			return (center - 160) / 8;

		case AxisCameraParams::kResolution_640x480:
		case AxisCameraParams::kResolution_640x360:
		default:
			return (center - 320) / 16;
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
	mkdir (m_directory);
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

/*
 * @brief Grabs a frame from the camera and saves it to the file system
 */
void Camera::SaveImageToFTP() const
{
	printf("the width of the image is: %i\n",m_image.GetWidth());
	printf("the height of the image is: %i\n",m_image.GetHeight());
	m_image.Write("/tmp/raw.jpg");
	printf("image successfully written");
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

				if (saveProcessedImages)
				{
					// TESTING ONLY - Delete this line
					//For testing purposes, prints the particle reports to the Console.
					printf("particle: %d center_mass_x: %d\n", i, particle.center_mass_x);
				}
			}
		}

		if (saveProcessedImages)
		{
			// TESTING ONLY - Delete this line
			printf("\n");
		}

		const UINT32 now = GetFPGATime();
		m_frameProcessingTime = frameStart - now;
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
	const Synchronized sync (m_cameraSemaphore);
	char path[60];
	sprintf (path, "%s/Img%04d_%s", m_directory, m_imageNo, name);
	image.Write(path);
}
