#include "BSBotDrive.h"
#include "../CommandBase.h"
#include <Math.h>

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

/** @brief Initializes the drive motors.
 *
 * Note the use of the comma operator (see http://en.wikipedia.org/wiki/Comma_operator)
 * which is used to print the initialization prior to the CANJaguar construction
 * which can be helpful when a device on the can bus does not respond
 *
 * @author Stephen Nutt
 */
DriveMotors::DriveMotors() try :
	m_frontLeftMotor ((printf("Initializing front left jaguar. \n"), k_frontLeftJaguar)),
	m_frontRightMotor ((printf("Initializing front right jaguar. \n"), k_frontRightJaguar)),
	m_rearLeftMotor ((printf("Initializing rear left jaguar. \n"), k_rearLeftJaguar)),
	m_rearRightMotor ((printf("Initializing rear right jaguar. \n"), k_rearRightJaguar))
{
	m_frontLeftMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	m_frontLeftMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	m_frontLeftMotor.EnableControl();

	m_frontRightMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	m_frontRightMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	m_frontRightMotor.EnableControl();

	m_rearLeftMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	m_rearLeftMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	m_rearLeftMotor.EnableControl();

	m_rearRightMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	m_rearRightMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	m_rearRightMotor.EnableControl();

	printf("Drive jaguars successfully created. \n");
}
catch (exception e)
{
	printf("Error creating jaguars.");
	printf(e.what());
}

/**
 * @brief This class constructs the instance
 * of the Robot Drive that we use on the robot.
 * 
 * @author Arthur Lockman
 */
BSBotDrive::BSBotDrive():
	RobotDrive(DriveMotors::m_rearRightMotor, DriveMotors::m_rearLeftMotor, 
			DriveMotors::m_frontRightMotor, DriveMotors::m_frontLeftMotor)
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
	// Don't ramp the PWM, actually stop them!
	DriveMotors::m_rearRightMotor.Set(0.0); 
	DriveMotors::m_rearLeftMotor.Set(0.0);
	DriveMotors::m_frontRightMotor.Set(0.0);
	DriveMotors::m_frontLeftMotor.Set(0.0);
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
	DriveMotors::m_rearRightMotor.Set(-rearRight); 
	DriveMotors::m_rearLeftMotor.Set(rearLeft);
	DriveMotors::m_frontRightMotor.Set(-frontRight);
	DriveMotors::m_frontLeftMotor.Set(frontLeft);
}
