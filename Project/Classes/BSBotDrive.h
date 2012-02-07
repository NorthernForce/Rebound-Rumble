#ifndef BSBOTDRIVE_H
#define BSBOTDRIVE_H
#include <WPILib.h>
#include "../Robotmap.h"
#include "XboxJoystick.h"

/** @brief Initializes the drive motors
 *
 * @author Stephen Nutt
 */
class DriveMotors
{
protected:
	DriveMotors();
	CANJaguar m_frontLeftMotor;
	CANJaguar m_frontRightMotor;
	CANJaguar m_rearLeftMotor;
	CANJaguar m_rearRightMotor;
};

/*
 * @brief This is the robot drive class. This class
 * extends the WPILib robotdrive class to contain 
 * the real drive code that we need to use to drive
 * our BS bot chassis.
 *
 * Note this has two base classes, DriveMotors which is declared before
 * RobotDrive.  This allows the RobotDrive constructor to use the motors
 * that are initialized in the DriveMotors class
 *
 * @author Arthur Lockman
 */
class BSBotDrive :
	private DriveMotors,
	public RobotDrive
{
private:
	void PowerMotors (float frontLeft, float frontRight);
	void PowerMotors (float frontLeft, float rearLeft, float frontRight, float rearRight);
public:
	BSBotDrive();
	//! Drives the robot using an XBox controller
	void ArcadeDrive (XboxJoystick& controller);
	//! Drives the robot using move and rotate values
	void ArcadeDrive (float moveValue, float rotateValue, bool squaredInputs);
	//! Alternate drive to move the robot using move and rotate values
	void ArcadeDrive2 (float moveValue, float rotateValue, bool squaredInputs);
	//! Turns on and off the use of the encoders
	void EnableEncoders (bool enable);
	//! Stops the robot
	void Stop();
};
#endif