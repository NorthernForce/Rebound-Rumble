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

void Drive::DriveWithStick(XboxJoystick& stick)
{
	drive->ArcadeDrive(stick);
}
