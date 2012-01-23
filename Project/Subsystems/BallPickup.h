#ifndef BALLPICKUP_H
#define BALLPICKUP_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @brief This class controls the ball
 * pickup mechanism on the robot. It contains
 * all classes for interacting with the 
 * pickup device.
 *
 * @author Arthur Lockman
 */
class BallPickup: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	BallPickup();
	void Spinup();
	void Stop();
	bool HasBall();
	void InitDefaultCommand();
};

#endif
