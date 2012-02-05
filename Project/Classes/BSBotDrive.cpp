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

const float rotateReduce = 1.5;

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
	RobotDrive(&CommandBase::s_motors->rearRightMotor, &CommandBase::s_motors->rearLeftMotor, 
			&CommandBase::s_motors->frontRightMotor, &CommandBase::s_motors->frontLeftMotor)
{
 	//Do nothing, as the whole class is set up.
}

/**
 * @brief Used to drive the robot with a joystick.
 * 
 * @param controller The XBoxJoystick to use to control the robot.
 */
void BSBotDrive::ArcadeDrive(XboxJoystick& controller)
{
	m_safetyHelper->Feed();
	const float x = controller.GetRawAxis (4);
	const float y = -controller.GetRawAxis (Joystick::kDefaultYAxis);
	this->ArcadeDrive (y, x, true);
}

/**
 * @brief Actually computes the values that the wheels need to 
 * turn to make the robot go.
 * 
 * @param moveValue The speed to move the robot N,S,E, or W.
 * @param rotateValue The rotational speed of the robot.
 * @param squaredInputs Whether or not the inputs are squared.
 */
void BSBotDrive::ArcadeDrive (
	float moveValue,
	float rotateValue,
	bool squaredInputs)
{
	// local variables to hold the computed PWM values for the motors
	float left;
	float right;

	moveValue   = Limit (moveValue);
	rotateValue = Limit (rotateValue) / rotateReduce;

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

/**
 * @brief Stops the robot.
 */
void BSBotDrive::Stop()
{
	// Don't ramp the PWM, actuall stop them!
	CommandBase::s_motors->rearRightMotor.Set(0.0); 
	CommandBase::s_motors->rearLeftMotor.Set(0.0);
	CommandBase::s_motors->frontRightMotor.Set(0.0);
	CommandBase::s_motors->frontLeftMotor.Set(0.0);
}

/**
 * @brief Powers the motors, given the speed of the front wheels. It
 * calculates the speed of the rear wheels, and passes it to the 
 * other PowerMotors method to actually power the motors to drive
 * the wheels.
 * 
 * @param frontLeft The speed of the front left motor.
 * @param frontRight The speed of the front right motor.
 */
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

/**
 * @brief Powers the motors, given the speed of the front and rear wheels.
 * This actually does the powering of the motors.
 * 
 * @param frontLeft The speed of the front left motor.
 * @param frontRight The speed of the front right motor.
 * @param rearLeft The speed of the rear left motor.
 * @param rearRight The speed of the rear right motor.
 */
void BSBotDrive::PowerMotors (
		float frontLeft,
		float rearLeft,
		float frontRight,
		float rearRight)
{
	CommandBase::s_motors->rearRightMotor.Set(-rearRight); 
	CommandBase::s_motors->rearLeftMotor.Set(rearLeft);
	CommandBase::s_motors->frontRightMotor.Set(-frontRight);
	CommandBase::s_motors->frontLeftMotor.Set(frontLeft);
}
