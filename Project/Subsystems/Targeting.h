#ifndef TARGETING_H
#define TARGETING_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @brief Handles the targeting math for the
 * shooter on the robot.
 *
 * @author Arthur Lockman
 */
class Targeting: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Targeting();
	float ShotVAngle();
	float ShotHAngle();
	float MuzzleSpeed();
	void InitDefaultCommand();
};

#endif
