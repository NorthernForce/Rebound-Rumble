#include "Targeting.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the targeting system.
 */
Targeting::Targeting() : Subsystem("Targeting") {
	
}
 
/**
 * @brief Initializes the default command for the subsystem.
 */
void Targeting::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Gets the vertical angle of the shot.
 * 
 * @return A float, the angle to turn to for the shot.
 */
float Targeting::ShotVAngle()
{
	return 0.0; //Not yet implemented.
}

/**
 * @brief Gets the horizontal angle of the shot.
 * 
 * @return A float, the angle to raise to for the shot.
 */
float Targeting::ShotHAngle()
{
	return 0.0; //Not yet implemented.
}

/**
 * @brief Gets the speed the ball needs to go to make the shot.
 * 
 * @return The speed, in voltage.
 */
float Targeting::MuzzleSpeed()
{
	return 0.0; //Not yet implemented.
}
