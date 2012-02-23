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
	void OI::SetTargetLEDs(bool target);
    JoystickButton m_imageButton;
    JoystickButton m_logAccelerometerButton;
//    DigitalIOButton m_fireButton;
    JoystickButton m_followButton;
	JoystickButton m_encoderEnableButton;
	JoystickButton m_encoderDisableButton;
	JoystickButton m_loadButton;
	JoystickButton m_raiseButton;
	JoystickButton m_lowerButton;
    JoystickButton m_startPickupButton;
    JoystickButton m_stopPickupButton;
    JoystickButton m_turnTurretLeft;
    JoystickButton m_turnTurretRight;
    JoystickButton m_lockTarget;
//    DigitalIOButton m_manualSwitch;
//    DigitalIOButton m_openChuteButton;
//    DigitalIOButton m_closeChuteButton;
//    DigitalIOButton m_feederSwitch;
//    DigitalIOButton m_lowerRampButton;
//	DriverStationLED m_noTargetLED;
//	DriverStationLED m_hasTargetLED;
//	DriverStationLED m_autoLED;
//	DriverStationLED m_manualLED;
private:
	XboxJoystick m_stick;
	Joystick m_manipulatorStick;
//	DriverStationEnhancedIO& m_driverstationEnhancedIO;
};

#endif
