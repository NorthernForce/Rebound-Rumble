#include "BSBotDrive.h"
#include "../CommandBase.h"
#include <Math.h>
#define M_PI 3.1415926535897932384626433832795

namespace
{
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
 * Exmaple SignedSquare (2) == 4 and SignedSquare (-2) == -4
 */
inline float SignedSquare (float val)
{
	return val < 0 ? - (val * val) : (val * val);
}
};

/**
 * @brief This class constructs the instance
 * of the Robot Drive that we use on the robot.
 * 
 * @author Arthur Lockman
 */
BSBotDrive::BSBotDrive():
	RobotDrive(CommandBase::s_motors->rearRightMotor, CommandBase::s_motors->rearLeftMotor, 
			CommandBase::s_motors->frontRightMotor, CommandBase::s_motors->frontLeftMotor)
{
 	//Do nothing, as the whole class is set up.
}

void BSBotDrive::ArcadeDrive(XboxJoystick& controller)
{
	m_safetyHelper->Feed();
	const float x = controller.GetRawAxis (4);
	const float y = - controller.GetRawAxis (Joystick::kDefaultYAxis);
	this->ArcadeDrive (y, x, true);
}

void BSBotDrive::ArcadeDrive (
	float moveValue,
	float rotateValue,
	bool squaredInputs)
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

	this->PowerMotors (left, right);
}

void BSBotDrive::Stop()
{
	// Don't ramp the PWM, actuall stop them!
	CommandBase::s_motors->rearRightMotor->Set(0.0); 
	CommandBase::s_motors->rearLeftMotor->Set(0.0);
	CommandBase::s_motors->frontRightMotor->Set(0.0);
	CommandBase::s_motors->frontLeftMotor->Set(0.0);
}

void BSBotDrive::PowerMotors (
	float frontLeft,
	float frontRight)
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

	this->PowerMotors (frontLeft, rearLeft, frontRight, rearRight);
}

void BSBotDrive::PowerMotors (
		float frontLeft,
		float rearLeft,
		float frontRight,
		float rearRight)
{
	CommandBase::s_motors->rearRightMotor->Set(-rearRight * 0.5); 
	CommandBase::s_motors->rearLeftMotor->Set(rearLeft * 0.5);
	CommandBase::s_motors->frontRightMotor->Set(-frontRight * 0.5);
	CommandBase::s_motors->frontLeftMotor->Set(frontLeft * 0.5);
}
