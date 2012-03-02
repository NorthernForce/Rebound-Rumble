#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include "Classes/XboxJoystick.h"
#include "DriverStationEnhancedIO.h"
#include "Classes/DriverStationLED.h"

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
	XboxJoystick& GetStick();
	XboxJoystick& GetManipulatorStick();
	void OI::SetTargetLEDs(bool target);
    
    //Xbox Controller Buttons
    //C prefix denotes a controller.
    JoystickButton c_YButton;
    JoystickButton c_XButton;
    JoystickButton c_AButton;
    JoystickButton c_BButton;
    JoystickButton c_BackButton;
    JoystickButton c_StartButton;
    JoystickButton c_LeftButton;
    JoystickButton c_RightButton;
    
    //2nd XBox Controller Buttons
    JoystickButton c2_YButton;
    JoystickButton c2_XButton;
    JoystickButton c2_AButton;
    JoystickButton c2_BButton;
    JoystickButton c2_BackButton;
    JoystickButton c2_StartButton;
    JoystickButton c2_LeftButton;
    JoystickButton c2_RightButton;
private:
	XboxJoystick m_driveStick;
	XboxJoystick m_manipulatorStick;
};

#endif
