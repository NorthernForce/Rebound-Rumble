#include "UltrasonicSensor.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the Ultrasonic sensor's subsystem.
 */
UltrasonicSensor::UltrasonicSensor() : Subsystem("UltrasonicSensor") {
	
}
    
/**
 * @brief Initializes the default command for the subsystem.
 */
void UltrasonicSensor::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Gets the distance that the nearest object
 * is in the line of sight of the sensor.
 * 
 * @returns A float, the distance in feet to the 
 * nearest object.
 */
float UltrasonicSensor::GetDistance()
{
	
}
