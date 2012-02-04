#include "OI.h"

/** 
 * @brief Constructs all of the Operator
 * Interface classes for interacting with
 * the robot.
 */
OI::OI():
	m_manipulatorStick(k_manipulatorJoystickPort)
{
	// Process operator interface input here.
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

/**
 * @brief Returns the manipulator joystick.
 * 
 * @return The manipluator joystick.
 */
Joystick& OI::GetManipulatorJoystick()
{
	return m_manipulatorStick;
}
