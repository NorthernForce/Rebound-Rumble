#include "OI.h"
#include "Robotmap.h"

/** 
 * @brief Constructs all of the Operator
 * Interface classes for interacting with
 * the robot.
 */
OI::OI():
	m_manipulatorStick(k_manipulatorJoystickPort),
	m_driverstationEnhancedIO(DriverStation::GetInstance()->GetEnhancedIO())
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

/**
 * @brief Gets the target that is selected on the 
 * operator console.
 * 
 * @return An int, the target that is selected.
 */
int OI::GetSelectedTarget()
{
	//@TODO fill in this stub.
	return 0;
}

/**
 * @brief Gets whether the fire button is pressed.
 * 
 * @return Bool, whether it's pressed or not.
 */
bool OI::GetFireButton()
{
	//@TODO fill in this stub.
	return false;
}

/**
 * @brief Get whether to capture some camera images.
 * 
 * @return Bool, whether to capture images.
 */
bool OI::GetCameraButton()
{
	return m_driverstationEnhancedIO.GetButton(1);
}
