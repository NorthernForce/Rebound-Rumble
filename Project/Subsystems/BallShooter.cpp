#include "BallShooter.h"
#include "../Robotmap.h"


/**
 * @brief The constructor for the ball shooter.
 */
ShooterMotors::ShooterMotors() try:
	m_flywheelFront((printf("Initializing front flywheel jaguar. \n"), k_flywheelFrontJaguar)),
	m_flywheelBack((printf("Initializing rear flywheel jaguar. \n"), k_flywheelBackJaguar))
{
	m_flywheelFront.ChangeControlMode(CANJaguar::kPercentVbus);
	m_flywheelFront.ConfigMaxOutputVoltage(12);
	m_flywheelFront.ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
	m_flywheelFront.EnableControl();

	m_flywheelBack.ChangeControlMode(CANJaguar::kPercentVbus);
	m_flywheelBack.ConfigMaxOutputVoltage(12);
	m_flywheelBack.ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
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
 * @param velocity A float, the speed in meters per second.
 * This should always be positive.
 */
void BallShooter::SetSpeed(float velocity)
{
//	m_flywheelFront.Set(velocity*30/(k_shooterWheelRadius*M_PI));
	//m_flywheelBack.Set(-velocity*30/(k_shooterWheelRadius*M_PI));
	m_flywheelFront.Set(velocity);
	m_flywheelBack.Set(-velocity);
}

//Gets the speed in meters per second of both wheels. "front" wheel is the x component
// and the "back" wheel is the y component.
Vector2D BallShooter::GetSpeed()
{
	return Vector2D(m_flywheelFront.GetSpeed()*(M_PI*k_shooterWheelRadius/30),m_flywheelBack.GetSpeed()*-(M_PI*k_shooterWheelRadius/30));
}

/**
 * @brief The constructor for the Ball Lifter.
 */
BallLifter::BallLifter():
		Subsystem("BallLifter"),
		m_liftLimit(1),
		m_liftMotor(k_liftMotorRelay,Relay::kBothDirections)
{
 	//Do nothing, as the whole class is set up.
}

/**
 * @brief Sets up the default command for the lifter.
 */
void BallLifter::InitDefaultCommand() {
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
