#include "CameraMount.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the Camera Mount 
 * housing. It has a pan and a tilt servo on 
 * it that can be interacted with to set the 
 * angle of the viewport on the camera.
 */
CameraMount::CameraMount() : Subsystem("CameraMount") {
	
}
    
/**
 * @brief Sets the default command for the subsystem.
 */
void CameraMount::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Sets the camera to a certain angle on 
 * its horizontal axis.
 * 
 * @param angle A float, the angle to set it to.
 */
void CameraMount::Pan(float angle)
{
	
}

/**
 * @brief Sets the camera to a certain angle on 
 * its vertical axis.
 * 
 * @param angle The angle to set it to.
 */
void CameraMount::Tilt(float angle)
{
	
}

/**
 * @brief Gets the angle that the pan servo 
 * is currently set to.
 * 
 * @return A float of the angle, relative to 0.
 */
float GetPanAngle()
{
	return 0.0; //Not yet implemented.
}

/**
 * @brief Gets the angle that the tilt servo 
 * is currently set to.
 * 
 * @return A float of the angle, relative to 0.
 */
float GetTiltAngle()
{
	return 0.0; //Not yet implemented.
}
