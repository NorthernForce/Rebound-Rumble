#ifndef XBOXJOYSTICK_H
#define XBOXJOYSTICK_H
#include <WPILib.h>
#include "../Robotmap.h"
#include "Joystick.h"
/*
 * @brief This class is the driver for the XBox Joystick
 * that we use at competition to control the robot.
 * All of the values returned by this class are 
 * already adjusted for the deadband in the controller itself.
 * 
 * @author Joseph Martin
 */
class XboxJoystick: public Joystick {
private:
    float Deadband;
    void CalculateDeadband();
	float DeadbandAdjust(float);
public:
	XboxJoystick(int port);
	float GetX(JoystickHand);
	float GetY(JoystickHand);
    float GetMagnitude();
    float GetRotation();
};
#endif
