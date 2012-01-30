#ifndef DRIVE_H
#define DRIVE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Classes/XboxJoystick.h"
#include "../CommandBase.h"

/**
 * @brief The drive object for the robot. All
 * methods for interacting with drive will go
 * here.
 *
 * @author Arthur Lockman
 */
class Drive: public Subsystem, public RobotDrive {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void PowerMotors(float frontLeft, float frontRight);
public:
	Drive();
	void InitDefaultCommand();
	void DriveRobot(GenericHID& joystick);
	void _DriveRobot(float moveValue, float rotateValue, bool squaredInputs);
	void Stop();
};

#endif
