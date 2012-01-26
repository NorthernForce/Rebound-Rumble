#include "Camera.h"
#include "../Robotmap.h"

/**
 * @brief Creates the camera object.
 */
Camera::Camera() : Subsystem("Camera") 
{
	
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
