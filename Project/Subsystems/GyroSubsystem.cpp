#include "GyroSubsystem.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the Gyro subsystem.
 */
GyroSubsystem::GyroSubsystem() : Subsystem("Gyro") {
	
}
    
/**
 * @brief Initializes the default command for the subsystem.
 */
void GyroSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Gets the current angle of the gyro.
 * 
 * @return Float, the angle that the gyro is turned to
 * relative to the starting point.
 */
float GyroSubsystem::GetAngle()
{
	return 0.0; //Not yet implemented.
}

/**
 * @brief Resets the Gyro to 0.
 */
void GyroSubsystem::Reset()
{
	
}

/**
 * @brief Gets the current rotational speed
 * of the robot.
 * 
 * @returns A float, the speed of the robot's rotation.
 */
float GyroSubsystem::GetRotationalSpeed()
{
	return 0.0; //Not yet implemented.
}
