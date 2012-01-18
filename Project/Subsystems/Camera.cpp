#include "Camera.h"
#include "../Robotmap.h"

/**
 * Create the camera object.
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
 * Initialize the camera and the tracking
 * code to do the tracking, set all 
 * variables, and connect to the driver
 * station to display images.
 */
void Camera::InitCamera() 
{
	
}

/**
 * Returns the distance to the target.
 * @return double Distance, in feet.
 */
double Camera::GetDistanceToTarget()
{
	
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
