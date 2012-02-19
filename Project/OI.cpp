#include "OI.h"
#include "Commands/CaptureImages.h"
#include "Commands/ChangeControlMode.h"
#include "Commands/Fire.h"
#include "Robotmap.h"

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
	m_encoderEnableButton(&m_stick, k_XBoxButtonBack),
	m_encoderDisableButton(&m_stick, k_XBoxButtonStart),
    m_stick(),
	m_driverstationEnhancedIO(DriverStation::GetInstance()->GetEnhancedIO())
{
	// Process operator interface input here.
    m_ImageButton.WhenPressed(new CaptureImages());
    m_fireButton.WhenPressed(new Fire());
    m_encoderEnableButton.WhenPressed(new ChangeControlMode(true));
    m_encoderDisableButton.WhenPressed(new ChangeControlMode(false));
    
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
