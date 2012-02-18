#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include "Classes/XboxJoystick.h"
#include "DriverStationEnhancedIO.h"
#include "Classes/DriverStationLED.h"
#include "Classes/EnhancedIOButton.h"

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
    JoystickButton m_ImageButton;
//	EnhancedIOButton m_fireButton;
//	EnhancedIOButton m_rejectbutton;
//	EnhancedIOButton m_manualSwitch;
//	EnhancedIOButton m_openChuteButton;
//	EnhancedIOButton m_closeChuteButton;
//	EnhancedIOButton m_feederSwitch;
//	EnhancedIOButton m_lowerRampButton;
//	DriverStationLED m_noTargetLED;
//	DriverStationLED m_hasTargetLED;
//	DriverStationLED m_autoLED;
//	DriverStationLED m_manualLED;
	
private:
	Joystick m_manipulatorStick;
	XboxJoystick m_stick;
	DriverStationEnhancedIO& m_driverstationEnhancedIO;
};

#endif
