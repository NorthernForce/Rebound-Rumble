#include "Drive.h"
#include "../Robotmap.h"
#include "../CommandBase.h"
#include <Math.h>
#include "../Classes/XboxJoystick.h"
#include "../Commands/DriveWithJoystick.h"
#define M_PI 3.1415926535897932384626433832795

namespace
{
//@TODO: Check these values.
//! The robot wheel base
const float wheelBase = 25.0;
//! The robot track (assumes front and rear track is the same)
const float wheelTrack = 22.25;
//! The ratio of wheelBase to wheelTrack
const float wheelRatio = wheelBase / wheelTrack;
const float bigWheelDiameter = 12.5;
const float mecanumWheelDiameter = 5.5;
const unsigned encoderPulsesPerRevolution = 90;
const float bigWheelDistancePerPulse = bigWheelDiameter * M_PI / encoderPulsesPerRevolution;
const float mecanumWheelDistancePerPulse = mecanumWheelDiameter * M_PI / encoderPulsesPerRevolution;
const float ramp = 0.2;

/**
 * @brief Returns the square of the val preserving the sign of val
 *
 * @example SignedSquare (2) == 4 and SignedSquare (-2) == -4
 */
inline float SignedSquare (float val)
{
	return val < 0 ? - (val * val) : (val * val);
}
};

/**
 * @brief The constructor for the Drive subsystem.
 */
Drive::Drive() : Subsystem("Drive"),
		RobotDrive (&CommandBase::s_motors->rearRightMotor, &CommandBase::s_motors->rearLeftMotor, 
						&CommandBase::s_motors->frontRightMotor, &CommandBase::s_motors->frontLeftMotor)
{
	
}
    
/**
 * @brief Sets up the default command for the subsystem.
 */
void Drive::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystick());
}

/**
 * @brief Drives the robot, with a given joystick input. 
 * 
 * @param joystick The joystick to read input from.
 */
void Drive::DriveRobot(GenericHID& joystick)
{
	const float x = joystick.GetRawAxis (4);
	const float y = - joystick.GetRawAxis (Joystick::kDefaultYAxis);
	this->_DriveRobot (y, x, true);
}

/**
 * @brief Internal. Drives the robot.
 */
void Drive::_DriveRobot(float moveValue, float rotateValue, bool squaredInputs)
{
	// local variables to hold the computed PWM values for the motors
		float left;
		float right;

		moveValue   = Limit (moveValue);
		rotateValue = Limit (rotateValue);

		if (squaredInputs)
		{
			// square the inputs (while preserving the sign) to increase fine control while permitting full power
			moveValue = SignedSquare (moveValue);
			rotateValue = SignedSquare (rotateValue);
		}

		if (moveValue >= 0.0)
		{
			if (rotateValue > 0.0)
			{
				left = moveValue - rotateValue;
				right = max (moveValue, rotateValue);
			}
			else
			{
				left = max (moveValue, -rotateValue);
				right = moveValue + rotateValue;
			}
		}
		else
		{
			if (rotateValue > 0.0)
			{
				left = -max (-moveValue, rotateValue);
				right = moveValue + rotateValue;
			}
			else
			{
				left = moveValue - rotateValue;
				right = -max (-moveValue, -rotateValue);
			}
		}
	this->PowerMotors(left, right);
}

/**
 * @brief Powers the motors. Takes the speed for the front left
 * and front right motor, and calculates the speed of the rear
 * mecanum wheels.
 * 
 * @param frontLeft The speed of the front left motor.
 * @param frontRight The speed of the front right motor.
 */
void Drive::PowerMotors(float frontLeft, float frontRight)
{
	// Calculate the desired rear mecanum speeds.
	float rearLeft  = frontLeft  * (0.5 + wheelRatio) + frontRight * (0.5 - wheelRatio);
	float rearRight = frontRight * (0.5 + wheelRatio) + frontLeft  * (0.5 - wheelRatio);

	// Scale the rear speeds down if either of them exceed 1
	const float maxSpeed = max (fabs (rearLeft), fabs (rearRight));
	if (maxSpeed > 1.0)
	{
		rearLeft /= maxSpeed;
		rearRight /= maxSpeed;
	}
	
	//Power the motors.
	//@TODO: figure out if these motor values are correct (positive and negatives).
	CommandBase::s_motors->frontLeftMotor.Set (-frontRight);
	CommandBase::s_motors->rearLeftMotor.Set (rearLeft);
	CommandBase::s_motors->frontRightMotor.Set (-frontLeft);
	CommandBase::s_motors->rearRightMotor.Set (rearRight);
}
