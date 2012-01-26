#include "Motors.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the motors. This method
 * will instantiate all of the motor objects for the 
 * robot.
 * 
 * @author Arthur Lockman
 */
Motors::Motors() : Subsystem("Motors") {
	
}
    
void Motors::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
