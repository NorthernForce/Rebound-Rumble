#include "OI.h"

/** 
 * @brief Constructs all of the Operator
 * Interface classes for interacting with
 * the robot.
 */
OI::OI()
{
	// Process operator interface input here.
}

XboxJoystick& OI::GetStick()
{
	return m_stick;
}
