#ifndef DRIVE_H
#define DRIVE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @brief The drive object for the robot. All
 * methods for interacting with drive will go
 * here.
 *
 * @author Arthur Lockman
 */
class Drive: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void InitDrive();
public:
	Drive();
	void InitDefaultCommand();
};

#endif
