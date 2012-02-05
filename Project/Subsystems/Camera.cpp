#include "Camera.h"
#include "../Robotmap.h"

/**
 * @brief Creates the camera object.
 */
Camera::Camera() :
	Subsystem("Camera"),
	m_cam (AxisCamera::GetInstance()),
	m_imageProcessingTask ("ImageProcessing", (FUNCPTR)Camera::ImageProcessingTask, Task::kDefaultPriority + 10)
{
	m_imageProcessingTask.Start (reinterpret_cast<UINT32> (this));
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

/**
 * @brief Gets the apparent angle that the robot lies
 * on relative to a line perpendicular to the targets.
 * 
 * @return A float, the angle in degrees of deviation.
 */
float Camera::GetAngleToTarget()
{
	return 0.0; //Not yet implemented.
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
	Wait(8.0);
	printf("Setting camera parameters\n");
	m_cam.WriteResolution(AxisCamera::kResolution_320x240);
	m_cam.WriteCompression(20);
	m_cam.WriteBrightness(50);
	printf("Parameters set./n");

	while (true)
	{
		// Fill me in
		taskDelay (1000);
		SaveImageToFTP();
		Wait (10);
	}
}
