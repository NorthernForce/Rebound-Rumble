#ifndef BALLSHOOTER_H
#define BALLSHOOTER_H
#include <WPILib.h>
#include "../Classes/Vector2D.h"

/**
 * @brief These are the motors for the shooter on the robot.
 *
 * @author Arthur Lockman
 */
class ShooterMotors
{
protected:
	ShooterMotors();
	CANJaguar m_flywheelFront;
	CANJaguar m_flywheelBack;
};

class BallShooter: 
	private ShooterMotors,
	public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	BallShooter();
	void SetSpeed(float voltage);
	void InitDefaultCommand();
    Vector2D GetSpeed();
};

class BallLifter:
	public Subsystem {
private:
	DigitalInput m_liftLimit;
	Relay m_liftMotor;
public:
	BallLifter();
	void EnableLift();
	void DisableLift();
	void InitDefaultCommand();
	bool GetLimit();
};

#endif
