#include "Drive.h"
#include "../Robotmap.h"

Drive::Drive() : Subsystem("Drive") 
{
	
}
    
void Drive::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * Initiates all of the drive components.
 * Wheels, encoders, etc.
 */
void Drive::InitDrive() 
{
	
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
