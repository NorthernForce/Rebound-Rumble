#ifndef TARGETING_H
#define TARGETING_H
#include <WPILib.h>
#include "../Classes/Vector2D.h"

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
    Vector2D GetTargetDisp();
public:
	Targeting();
	float ShotVAngle();
	float ShotHAngle();
	float MuzzleSpeed();
	void InitDefaultCommand();
};

#endif
