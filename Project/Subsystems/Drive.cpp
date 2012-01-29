#include "Drive.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the Drive subsystem.
 */
Drive::Drive() : Subsystem("Drive"),
	robotDrive()
{
	
}
    
/**
 * @brief Sets up the default command for the subsystem.
 */
void Drive::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Drive::DriveRobot(GenericHID &controller)
{

}
