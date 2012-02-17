#include "OI.h"
#include "Commands/CaptureImages.h"
#include "Commands/Fire.h"
#include "Classes/EnhancedIOButton.h"
#include "Robotmap.h"

namespace
{
//!Digital Inputs/outputs on the PSoC module.
const int k_fireButton = 1;
const int k_rejectbutton = 2;
const int k_manualSwitch = 3;
const int k_openChuteButton = 4;
const int k_closeChuteButton = 5;
const int k_feederSwitch = 6;
const int k_noTargetLED = 7;
const int k_hasTargetLED = 8;
const int k_autoLED = 9;
const int k_manualLED = 10;
const int k_lowerRampButton = 11;
const int k_dIO12 = 12;

//!Analog inputs on the PSoC modules.
const int k_turretAngle = 1;
const int k_velocitySlider = 2;
const int k_aI3 = 3;
const int k_aI4 = 4;
const int k_aI5 = 5;
}
/** 
 * @brief Constructs all of the Operator
 * Interface classes for interacting with
 * the robot.
 */
OI::OI() try :
	m_ImageButton(&m_stick, k_XBoxButtonA),
    m_fireButton(k_fireButton),
    m_manualSwitch(k_manualSwitch),
    m_openChuteButton(k_openChuteButton),
    m_closeChuteButton(k_closeChuteButton),
    m_feederSwitch(k_feederSwitch),
    m_lowerRampButton(k_lowerRampButton),
	m_noTargetLED(k_noTargetLED),
	m_hasTargetLED(k_hasTargetLED),
	m_autoLED(k_autoLED),
	m_manualLED(k_manualLED),
	m_manipulatorStick(k_manipulatorJoystickPort),
    m_stick(),
	m_driverstationEnhancedIO(DriverStation::GetInstance()->GetEnhancedIO())
{
	// Process operator interface input here.
    m_ImageButton.WhenPressed(new CaptureImages());
    m_fireButton.WhenPressed(new Fire());
    
    printf("All OI elements created successfully.");
    printf("\n");
}
catch (exception e)
{
	printf("Operator Interface failed to initialize.");
}
/**
 * @brief Sets the LED's on the operator console.
 * 
 * @param target Whether it has a target or not.
 */
void OI::SetTargetLEDs(bool target)
{
	if (target)
	{
		m_hasTargetLED.TurnOn();
		m_noTargetLED.TurnOff();
	} else {
		m_hasTargetLED.TurnOff();
		m_noTargetLED.TurnOn();
	}
}

/**
 * @brief Returns the drive joystick.
 * 
 * @return The drive joystick.
 */
XboxJoystick& OI::GetStick()
{
	return m_stick;
}
