#include "BallShooter.h"
#include "../Robotmap.h"

static const float k_wheelRadius = 1.0;

/**
 * @brief The constructor for the ball shooter.
 */
ShooterMotors::ShooterMotors() try:

		m_flywheelFront((printf("Initializing front left jaguar. \n"), k_flywheelFront)),
		m_flywheelBack((printf("Initializing front left jaguar. \n"), k_flywheelBack))
{
	m_flywheelFront.ChangeControlMode(CANJaguar::kPercentVbus);
	m_flywheelFront.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	m_flywheelFront.EnableControl();
	
	m_flywheelBack.ChangeControlMode(CANJaguar::kPercentVbus);
	m_flywheelBack.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	m_flywheelBack.EnableControl();
	
	printf("Shooter jaguars successfully created. \n");
}
catch (exception e)
{
	printf("Error creating jaguars.");
	printf(e.what());
}
BallShooter::BallShooter():
		Subsystem("BallShooter")
	//DriveMotors::m_rearRightMotor, DriveMotors::m_rearLeftMotor, 
	//		DriveMotors::m_frontRightMotor, DriveMotors::m_frontLeftMotor)RobotDrive(
{
 	//Do nothing, as the whole class is set up.
}
/**
 * @brief Sets up the default command for the shooter.
 */
void BallShooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Sets the pitcher to spin at a set speed 
 * for startup.
 * 
 * @param speed A float, the speed in voltage of the pitcher.
 * This should always be positive.
 */
void BallShooter::SetSpeed(float velocity)
{
	m_flywheelFront.Set(velocity*30/(k_wheelRadius*M_PI));
	m_flywheelBack.Set(velocity*30/(k_wheelRadius*M_PI));
}

Vector2D BallShooter::GetSpeed()
{
	return Vector2D(m_flywheelFront.Get()*(M_PI/30),m_flywheelBack.Get()*(M_PI/30));
}

/**
 * @brief The constructor for the Ball Lifter.
 */
BallLifter::BallLifter():
		Subsystem("BallLifter"),
		m_liftLimit(k_liftLimit),
		m_liftMotor(k_liftMotorRelay,Relay::kBothDirections)
{
 	//Do nothing, as the whole class is set up.
}

/**
 * @brief Sets up the default command for the lifter.
 */
void BallLifter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Turns the lift on.
 */
void BallLifter::EnableLift()
{
	m_liftMotor.Set(Relay::kForward);
}

/**
 * @brief Turns the lift off.
 */
void BallLifter::DisableLift()
{
	m_liftMotor.Set(Relay::kOff);
}

/**
 * @brief Gets the state of the limit switch.
 * 
 * @return Bool, whether or not the limit is hit.
 */
bool BallLifter::GetLimit()
{
	return m_liftLimit.Get();
}
