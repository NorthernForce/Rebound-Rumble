#ifndef BALLSHOOTER_H
#define BALLSHOOTER_H
#include <WPILib.h>

/**
 * @brief This class contains all methods
 * for interacting with the ball shooter mechanism
 * on the robot. 
 *
 * @author Arthur Lockman
 */
class BallShooter: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	BallShooter();
	void Spinup(float speed);
	void InitDefaultCommand();
	void AdjustVerticalAngle(float angle);
	void AdjustPitcherSpeed(float speed);
	void Fire();
};

#endif
