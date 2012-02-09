#ifndef PNEUMATICS_H
#define PNEUMATICS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @brief The class for controlling the pneumatic
 * systems on the robot.
 *
 * @author Arthur Lockman
 */
class Pneumatics: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Pneumatics();
	void InitDefaultCommand();
};

#endif
