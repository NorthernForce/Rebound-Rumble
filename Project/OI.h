#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include "Classes/XboxJoystick.h"

/**
 * @brief All of the classes for interacting
 * with the operator interface go here. 
 * 
 * @author Arthur Lockman
 */
class OI {
private:
	
public:
	OI();
	//The XBox Joystick we're using to control the robot.
	XboxJoystick& GetStick();
	Joystick& GetManipulatorJoystick();
    JoystickButton GetImageButton();
	bool OI::GetFireButton();
	int OI::GetSelectedTarget();
	bool OI::GetCameraButton();
private:
	Joystick m_manipulatorStick;
	XboxJoystick m_stick;
    JoystickButton m_ImageButton;
	DriverStationEnhancedIO& m_driverstationEnhancedIO;
};

#endif
