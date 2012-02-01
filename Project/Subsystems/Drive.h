#ifndef DRIVE_H
#define DRIVE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Classes/XboxJoystick.h"
#include "../CommandBase.h"
#include "../Classes/BSBotDrive.h"

/**
 * @brief The drive object for the robot. All
 * methods for interacting with drive will go
 * here.
 *
 * @author Arthur Lockman
 */
class BSBotDrive;
class Drive: public Subsystem{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	BSBotDrive* drive;
public:
	Drive();
	void InitDefaultCommand();
	void DriveWithStick(XboxJoystick stick);
};

#endif
