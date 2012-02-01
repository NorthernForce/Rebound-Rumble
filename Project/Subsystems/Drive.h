#ifndef DRIVE_H
#define DRIVE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
<<<<<<< .working
#include "../Classes/XboxJoystick.h"
#include "../CommandBase.h"
=======
#include "../Classes/XboxJoystick.h"
#include "../CommandBase.h"
#include "../Classes/BSBotDrive.h"
>>>>>>> .merge-right.r423

/**
 * @brief The drive object for the robot. All
 * methods for interacting with drive will go
 * here.
 *
 * @author Arthur Lockman
 */
<<<<<<< .working
class Drive: public Subsystem{
=======
class BSBotDrive;
class Drive: public Subsystem{
>>>>>>> .merge-right.r423
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
<<<<<<< .working
	void PowerMotors(float frontLeft, float frontRight);
	RobotDrive *drive;
=======
	BSBotDrive* drive;
>>>>>>> .merge-right.r423
public:
	Drive();
	void InitDefaultCommand();
<<<<<<< .working
	void DriveRobot(XboxJoystick* joystick);
	void _DriveRobot(float moveValue, float rotateValue, bool squaredInputs);
	void Stop();
=======
	void DriveWithStick(XboxJoystick stick);
>>>>>>> .merge-right.r423
};

#endif
