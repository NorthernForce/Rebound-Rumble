#include "Drive.h"
#include "../Robotmap.h"
#include "../CommandBase.h"
#include "../Commands/DriveWithJoystick.h"
#include "../Classes/BSBotDrive.h"

/**
 * @brief The constructor for the Drive subsystem.
 */
Drive::Drive() : Subsystem("Drive")
{
	drive = new BSBotDrive();
}

/**
 * @brief Sets up the default command for the subsystem.
 */
void Drive::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystick());
}

/**
 * @brief Changes the control mode of the jaguars.
 * 
 * @param enable Whether to enable the encoders or not.
 */
void Drive::ChangeControlMode(bool enable)
{
	drive->UseEncoders(enable);
}

void Drive::DriveWithStick(XboxJoystick& stick)
{
	drive->ArcadeDrive(stick);
}
/** @brief Drives the robot the specified 
 *
 * @author Stephen Nutt
 */
void Drive::DriveRobot (
	float speed,
	float direction)
{
	drive->ArcadeDrive (speed, direction, false);
}

double Drive::GetAvgSpeed() const// Gets average speed in meters per second
{
    return drive->GetAvgSpeed();
}
