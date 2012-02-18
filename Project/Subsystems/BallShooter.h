#ifndef BALLSHOOTER_H
#define BALLSHOOTER_H
#include <WPILib.h>
#include "../Classes/Vector2D.h"

/**
 * @brief This class contains all methods
 * for interacting with the ball shooter mechanism
 * on the robot. 
 *
 * @author Arthur Lockman
 */
class ShooterMotors
{
protected:
	ShooterMotors();
	CANJaguar m_flywheelFront;
	CANJaguar m_flywheelBack;
	Relay m_liftMotor;
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
	void AdjustVerticalAngle(float angle);
	void Fire();
    Vector2D GetSpeed();
};

#endif
