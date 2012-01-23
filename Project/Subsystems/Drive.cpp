#include "Drive.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the Drive subsystem.
 */
Drive::Drive() : Subsystem("Drive") 
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

/**
 * @brief Initiates all of the drive components.
 * Wheels, encoders, etc.
 */
void Drive::InitDrive() 
{
	
}
