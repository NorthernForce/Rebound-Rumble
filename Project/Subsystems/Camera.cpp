#include <vxWorks.h>
#include "Camera.h"
#include "../Robotmap.h"
#include "Vision/BinaryImage.h"

/**
 * @brief Creates the camera object.
 */
Camera::Camera() :
	Subsystem("Camera"),
	m_cam (AxisCamera::GetInstance()),
	m_imageProcessingTask ("ImageProcessing", (FUNCPTR)Camera::ImageProcessingTask, Task::kDefaultPriority + 10)
{
	m_imageProcessingTask.Start (reinterpret_cast<UINT32> (this));
	m_particleSemaphore = semBCreate (SEM_Q_PRIORITY, SEM_EMPTY);
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
float Camera::GetDistanceToTarget()
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
	semTake(m_particleSemaphore, WAIT_FOREVER);
	const bool hasTarget = !m_particles.empty();
	semGive(m_particleSemaphore);
	return hasTarget;
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
float Camera::GetAngleToTarget()
{
	Rect topTarget;
	topTarget.top = INT_MAX;

	// We need to lock m_particleSemaphore to protect access
	// to m_particles
	semTake(m_particleSemaphore, WAIT_FOREVER);
	for (size_t i = 0; i < m_particles.size(); ++i)
	{
		Rect& r = m_particles[i].boundingRect;
		if (r.top < topTarget.top)
		{
			topTarget = r;
		}
	}
	semGive(m_particleSemaphore);

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

/*
 * @brief Grabs a frame from the camera and saves it to the file system
 */
void Camera::SaveImageToFTP()
{
	m_cam.GetImage(&m_image);
	printf("the width of the image is: %i\n",m_image.GetWidth());
	printf("the height of the image is: %i\n",m_image.GetHeight());
	m_image.Write("/tmp/t.jpg");
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
	Wait(8.0);
	printf("Setting camera parameters\n");
	m_cam.WriteResolution(AxisCamera::kResolution_320x240);
	m_cam.WriteCompression(20);
	m_cam.WriteBrightness(50);
	printf("Camera parameters set./n");

	while (true)
	{
		// Wait for a new image to be available
		if (m_cam.IsFreshImage() == false)
		{
			taskDelay (2);
			continue;
		}

		// TESTING ONLY - Delete this line
		SaveImageToFTP();

		//@TODO correct HSL thresholds.
		Threshold violetThreshold(226, 255, 28, 255, 96, 255);
		BinaryImage *violetPixels = m_image.ThresholdHSL(violetThreshold);
		BinaryImage *bigObjectsImage = violetPixels->RemoveSmallObjects(false, 2);
		BinaryImage *convexHullImage = bigObjectsImage->ConvexHull(false);
		const int particleCount = convexHullImage->GetNumberParticles();

		// Save the particle analysis for use by the main thread.
		// We need to lock m_particleSemaphore to protect access
		// to m_particles
		semTake(m_particleSemaphore, WAIT_FOREVER);
		m_particles.resize(particleCount);
		for (int i = 0; i < particleCount; ++i)
		{
			ParticleAnalysisReport& particle = m_particles[i];
			particle = convexHullImage->GetParticleAnalysisReport(i);

			// TESTING ONLY - Delete this line
			//For testing purposes, prints the particle reports to the Console.
			printf("particle: %d  center_mass_x: %d\n", i, particle.center_mass_x);
		}
		semGive(m_particleSemaphore);

		// TESTING ONLY - Delete this line
		printf("\n");

		//@TODO Verify these.
		delete violetPixels;
		delete convexHullImage;
		delete bigObjectsImage;
	}
}
