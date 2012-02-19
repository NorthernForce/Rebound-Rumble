#ifndef DRIVE_H
#define DRIVE_H
#include <WPILib.h>
#include "../Classes/BSBotDrive.h"

/**
 * @brief The drive object for the robot. All
 * methods for interacting with drive will go
 * here.
 *
 * @author Arthur Lockman
 */
class Drive: public Subsystem{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	BSBotDrive* drive;
public:
	Drive();
	void InitDefaultCommand();
	void DriveWithStick(XboxJoystick& stick);
	void DriveRobot (float speed, float direction);
	void ChangeControlMode (bool enable);
};

#endif
