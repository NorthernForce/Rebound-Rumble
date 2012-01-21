/*
 * XboxJoystick.cpp
 *
 *  Created on: Jan 10, 2012
 *      Author: Joseph Martin
 *
 */

#include "XboxJoystick.h"
#include "Joystick.h"

/**
 * @brief This class constructs the instance
 * of the XBox Joystick. It automatically 
 * calculates the deadband for the joysticks 
 * on the controller.
 * 
 * @author Arthur Lockman
 */
XboxJoystick::XboxJoystick(): 
	Joystick(k_XBoxJoystickPort) 
{
 	CalculateDeadband();
}

/**
 * @brief Gets the value from the X axis
 * of one of the joysticks on the controller.
 * 
 * @param hand The joystick hand to get,
 * kLeftHand or kRightHand.
 * 
 * @return A float of the value of the 
 * X axis of the joystick.
 * 
 * @author Joseph Martin
 */
float XboxJoystick::GetX(JoystickHand hand) 
{
	return DeadbandAdjust(Joystick::GetX(hand));
}

/**
 * @brief Gets the value from the Y axis
 * of one of the joysticks on the controller.
 * 
 * @param hand The joystick hand to get,
 * kLeftHand or kRightHand.
 * 
 * @return A float of the value of the 
 * Y axis of the joystick.
 * 
 * @author Joseph Martin
 */
float XboxJoystick::GetY(JoystickHand hand) 
{
	return DeadbandAdjust(Joystick::GetY(hand));
}

/**
 * @brief Gets the magnitude of the Y axis
 * left joystick on the controller, which
 * is used to find the speed that the robot
 * should be moving at.
 * 
 * @return A float, positive is forward, and 
 * negative is backwards.
 * 
 * @author Arthur Lockman
 */
float XboxJoystick::GetMagnitude()
{
    return GetY(Joystick::kLeftHand);
}

/**
 * @brief Gets the magnitude of the X axis
 * right joystick on the controller, which
 * is used to find the rotational direction
 * that the robot should be moving in.
 * 
 * @return A float, positive is right, and 
 * negative is left.
 * 
 * @author Arthur Lockman
 */
float XboxJoystick::GetRotation()
{
    return GetX(Joystick::kRightHand);
}

/**
 * @brief Calculates the deadband on the controller,
 * and sets the value for all other methods 
 * automatically.
 * 
 * @author Arthur Lockman
 */
void XboxJoystick::CalculateDeadband()
{
    Deadband = 0.1;
}

/**
 * @brief Calculates the value that the controller
 * should be returning based on the calculated
 * deadband value.
 * 
 * @param val The value to apply the deadband 
 * calculations to.
 * 
 * @return A float, the calculated value.
 * 
 * @author Arthur Lockman
 */
float XboxJoystick::DeadbandAdjust(float val) 
{
	if (val > Deadband) {
		return (val - Deadband) / (1 - Deadband);
	} else if (val < -Deadband) {
		return (val + Deadband) / (1 - Deadband);
	} else {
		return 0;
	}
}
