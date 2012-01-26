#include "AccelerometerSubsystem.h"
#include "../Robotmap.h"

/**
 * @brief Constructor for the Accelerometer Subsystem. 
 * Creates the Accelerometer object.
 * 
 * @author Arthur Lockman
 */
AccelerometerSubsystem::AccelerometerSubsystem() : Subsystem("AccelerometerSubsystem") {
	
}

/**
 * @brief Sets the default command for the subsystem.
 */
void AccelerometerSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Gets the value from the accelerometer.
 * 
 * @return A float, the value that the accelerometer
 * reads in.
 * 
 * @author Arthur Lockman
 */
float AccelerometerSubsystem::GetAccelValue()
{
	return 0.0; //Not yet implemented.
}
