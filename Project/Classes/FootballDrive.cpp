#include "FootballDrive.h"
#include <Math.h>
#include "../Robotmap.h"
#include "../CommandBase.h"
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
 * Returns the square of the val preserving the sign of val
 *
 * Exmaple SignedSquare (2) == 4 and SignedSquare (-2) == -4
 */
inline float SignedSquare (float val)
{
	return val < 0 ? - (val * val) : (val * val);
}
};

/** @brief Constructs an instance of the FootballDrive object
 *
 */
FootballDrive::FootballDrive (
	float sensitivity):
		RobotDrive (&CommandBase::s_motors->rearRightMotor, &CommandBase::s_motors->rearLeftMotor, 
				&CommandBase::s_motors->frontRightMotor, &CommandBase::s_motors->frontLeftMotor)
{
	
}

void FootballDrive::ArcadeDrive (
	GenericHID& controller)
{
	const float x = controller.GetRawAxis (4);
	const float y = - controller.GetRawAxis (Joystick::kDefaultYAxis);
	this->ArcadeDrive (y, x, true);
}

/** @brief First drive system
 * 
 * When \c moveValue is 0 the robot will spin if \c rotateValue is not 0
 * 
 */
void FootballDrive::ArcadeDrive (
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

/** @brief Second drive system
 * 
 * When \c powerValue is 0 the robot will not move or spin
 *
 * See Conor for more details
 * 
 */
void FootballDrive::ArcadeDrive2 (float moveValue, float rotateValue, bool squaredInputs)

{
	float left;
	float right;
	float theta;
	
	moveValue   = Limit(moveValue);
	rotateValue = -Limit(rotateValue);

	if (squaredInputs)
	{
		// square the inputs (while preserving the sign) to increase fine control while permitting full power
		moveValue = SignedSquare (moveValue);
		rotateValue = SignedSquare (rotateValue);
	}

	if(moveValue < 0)
		theta = -acos(rotateValue) + (M_PI / 4);
	else
		theta = acos(rotateValue) + (M_PI / 4);
	
	left = fabs(moveValue) * ((sin(theta)) / (max((fabs(sin(theta))), (fabs(-(cos(theta)))))));
	right = fabs(moveValue) * ((-(cos(theta))) / (max((fabs(sin(theta))), (fabs(-(cos(theta)))))));

	this->PowerMotors (left, right);

}

/** @brief Stops the robot by setting all PWMs to speed 0
 *
 */
void FootballDrive::Stop()
{
	// Don't ramp the PWM, actuall stop them!
	
	CommandBase::s_motors->frontLeftMotor.Set(0.0);
	CommandBase::s_motors->rearLeftMotor.Set(0.0);
	CommandBase::s_motors->frontRightMotor.Set(0.0);
	CommandBase::s_motors->rearRightMotor.Set(0.0);
}

/** @brief Derives the power for the rear mecanum wheels from the power to the
 * front wheels.
 *
 * The two front large wheels dictate the speed and direction of the robot
 * and the two rear mecanum wheels are a "powered assist".  Knowing the desired
 * speeds of the front wheels we can calculate the optimum speed of the rear
 * wheels.
 */
void FootballDrive::PowerMotors (
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

/** @brief Powers the four wheels by ramping the power towards the desired
 * values
 *
 * The motors are gradually powered up and down to reduce excessive torque
 * placed on the drive train when going from full ahead to full reverse.
 */
void FootballDrive::PowerMotors (
		float frontLeft,
		float rearLeft,
		float frontRight,
		float rearRight)
{
	frontLeft  *= m_invertedMotors[kFrontLeftMotor];
	rearLeft   *= m_invertedMotors[kRearLeftMotor];
	frontRight *= m_invertedMotors[kFrontRightMotor];
	rearRight  *= m_invertedMotors[kRearRightMotor];

	// Switched front wheel PWM values
	CommandBase::s_motors->frontLeftMotor.Set (-frontRight);
	CommandBase::s_motors->rearLeftMotor.Set (rearLeft);
	CommandBase::s_motors->frontRightMotor.Set (-frontLeft);
	CommandBase::s_motors->rearRightMotor.Set (rearRight);
}
