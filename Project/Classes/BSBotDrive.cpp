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

const float ramp = .4;
const float velocityLimit = 1.0;
const float rampVelocityLimit = 0.75;
const float tolerance = 0.2;
const float thereTolerance = 0.1;

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
	m_frontLeftMotor ((printf("Initializing front left jaguar. \n"), k_frontLeftJaguar), ramp, velocityLimit, tolerance, thereTolerance),
	m_frontRightMotor((printf("Initializing front right jaguar. \n"), k_frontRightJaguar), ramp, velocityLimit, tolerance, thereTolerance),
	m_rearLeftMotor  ((printf("Initializing rear left jaguar. \n"), k_rearLeftJaguar), ramp, velocityLimit, tolerance, thereTolerance),
	m_rearRightMotor ((printf("Initializing rear right jaguar. \n"), k_rearRightJaguar), ramp, velocityLimit, tolerance, thereTolerance)
{
	printf("Drive jaguars successfully created. \n\r");

	DriveMotors::m_frontLeftMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	DriveMotors::m_frontLeftMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_frontRightMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	DriveMotors::m_frontRightMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_rearLeftMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	DriveMotors::m_rearLeftMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_rearRightMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	DriveMotors::m_rearRightMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	printf("Drive jaguars successfully instantiated\n\r");
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
    DriveMotors(),
	RobotDrive(DriveMotors::m_rearRightMotor, DriveMotors::m_rearLeftMotor,
			DriveMotors::m_frontRightMotor, DriveMotors::m_frontLeftMotor),
	m_encodersOn (true),
	m_useEncoders (k_useEncoders)
{
	// Initially the encoders set as on so powering the motors to 0,0
	// will disable use of the encoders
	this->PowerMotors (0.0, 0.0);
	this->Stop();
}

/**
 * @brief Used to drive the robot with a joystick.
 *
 * @param controller The XBoxJoystick to use to control the robot.
 */
void BSBotDrive::ArcadeDrive(XboxJoystick& controller)
{
	m_safetyHelper->Feed();
	float rotateValue = controller.GetRawAxis (4);
	const float moveValue = -controller.GetRawAxis (Joystick::kDefaultYAxis);
	this->ArcadeDrive (moveValue, -rotateValue, true);
}

//! Turns on and off the use of the encoders
void BSBotDrive::UseEncoders (bool enable)
{
	m_useEncoders = enable;
	printf(m_useEncoders ? "Encoders on.\n\r" : "Encoders off\r\n");
}

/**
 * @brief Changes the control mode of the jaguars.
 *
 * @param enable Whether to turn the encoders on or off.
 *
 * @author Arthur Lockman
 */
void BSBotDrive::EnableEncoders(bool enable)
{
	// Nothing to do if the system it currently set as desired
	if (enable == m_encodersOn) return;

	if (enable)
	{
		DriveMotors::m_frontLeftMotor.ChangeControlMode(CANJaguar::kSpeed);
		DriveMotors::m_frontLeftMotor.SetPID(k_driveP,k_driveI,k_driveD);
		DriveMotors::m_frontLeftMotor.ConfigEncoderCodesPerRev(k_encoderPulsesPerRev);
		DriveMotors::m_frontLeftMotor.SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);

		DriveMotors::m_frontRightMotor.ChangeControlMode(CANJaguar::kSpeed);
		DriveMotors::m_frontRightMotor.SetPID(k_driveP,k_driveI,k_driveD);
		DriveMotors::m_frontRightMotor.ConfigEncoderCodesPerRev(k_encoderPulsesPerRev);
		DriveMotors::m_frontRightMotor.SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);

		DriveMotors::m_rearLeftMotor.ChangeControlMode(CANJaguar::kSpeed);
		DriveMotors::m_rearLeftMotor.SetPID(k_driveP,k_driveI,k_driveD);
		DriveMotors::m_rearLeftMotor.ConfigEncoderCodesPerRev(k_encoderPulsesPerRev);
		DriveMotors::m_rearLeftMotor.SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);

		DriveMotors::m_rearRightMotor.ChangeControlMode(CANJaguar::kSpeed);
		DriveMotors::m_rearRightMotor.SetPID(k_driveP,k_driveI,k_driveD);
		DriveMotors::m_rearRightMotor.ConfigEncoderCodesPerRev(k_encoderPulsesPerRev);
		DriveMotors::m_rearRightMotor.SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	} else {
		DriveMotors::m_frontLeftMotor.ChangeControlMode(CANJaguar::kPercentVbus);

		DriveMotors::m_frontRightMotor.ChangeControlMode(CANJaguar::kPercentVbus);

		DriveMotors::m_rearLeftMotor.ChangeControlMode(CANJaguar::kPercentVbus);

		DriveMotors::m_rearRightMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	}

	if (enable == m_encodersOn) return;
}

float BSBotDrive::Limit(float input, float max)
{
    if (input > max)
    {
        return max;
    } else if (input < -max)
    {
        return -max;
    }
    return input;
}

/**
 * @brief Actually computes the values that the wheels need to
 * turn to make the robot go.
 *
 * @param moveValue The speed to move the robot N, or S.
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
	Vector3D accelerations = CommandBase::s_accelerometer->GetAccelerations();
	float limit;
	if((acos(Limit(accelerations.z,1)) > M_PI/18) &&
	   (k_maxMatchTime - DriverStation::GetInstance()->GetMatchTime() < 20))
	{
		limit = rampVelocityLimit;
	} else
	{
		limit = velocityLimit;
	}
	moveValue   = Limit (moveValue, limit);
	rotateValue = Limit (rotateValue, limit) / rotateReduce;

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
	DriveMotors::m_rearRightMotor.StopMotor();
	DriveMotors::m_rearLeftMotor.StopMotor();
	DriveMotors::m_frontRightMotor.StopMotor();
	DriveMotors::m_frontLeftMotor.StopMotor();
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
	// Enable the encoders if we are using them and going a non 0 speed
	EnableEncoders (m_useEncoders && (frontLeft != 0 || frontRight != 0));

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
	DriveMotors::m_rearRightMotor.SetOutput(-rearRight);
	DriveMotors::m_rearLeftMotor.SetOutput(rearLeft);
	DriveMotors::m_frontRightMotor.SetOutput(-frontRight);
	DriveMotors::m_frontLeftMotor.SetOutput(frontLeft);
}

/**
 * @brief Feeds the safety helper.
 */
void BSBotDrive::Feed()
{
	m_safetyHelper->Feed();
}
