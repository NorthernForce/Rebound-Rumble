#ifndef TARGETING_H
#define TARGETING_H
#include <WPILib.h>
#include "../Classes/Vector3D.h"
#include "../Classes/Aim.h"

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
    Vector3D GetTargetDisp();
public:
	Targeting();
    Aim GetAim();
	void InitDefaultCommand();
};

#endif
