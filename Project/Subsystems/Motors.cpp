#include "Motors.h"
#include "../Robotmap.h"
#include "CANJaguar.h"

/**
 * @brief The constructor for the motors. This method
 * will instantiate all of the motor objects for the 
 * robot.
 * 
 * @author Arthur Lockman
 */
Motors::Motors() : Subsystem("Motors"),
	frontLeftMotor(k_frontLeftJaguar),
	frontRightMotor(k_frontRightJaguar),
	rearLeftMotor(k_rearLeftJaguar),
	rearRightMotor(k_rearRightJaguar)
{
	
}
    
void Motors::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
