#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include "DriverStationEnhancedIO.h"
#include "Classes/DriverStationLED.h"
#include "Classes/FRCXboxJoystick.h"

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
	FRCXboxJoystick& GetStick();
	FRCXboxJoystick& GetManipulatorStick();
    
private:
	FRCXboxJoystick m_driveStick;
	FRCXboxJoystick m_manipulatorStick;
};

#endif
