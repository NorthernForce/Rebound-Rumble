#ifndef GYRO_H
#define GYRO_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @brief This controls the gyro sensor
 * that will go onto the robot. All methods
 * for interacting with the gyro go here.
 *
 * @author Arthur Lockman
 */
class GyroSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	GyroSubsystem();
	void InitDefaultCommand();
};

#endif
