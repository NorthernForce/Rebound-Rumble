#include "Targeting.h"
#include "../Robotmap.h"
#include <math.h>

/**
 * @brief The constructor for the targeting system.
 */
Targeting::Targeting() : Subsystem("Targeting") {

}

/**
 * @brief Gets the 2 dimensional displacement vector
 * between the position of the shooter and target
 *
 * @return 2D displacement vector to the target
 */
Vector2D Targeting::GetTargetDisp()
{
    //TODO: Make sure this function works correctly
    return Vector2D(); // Will this actually work? it compiles ok
    // Not sure it will allocate memory correctly.
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
	return atan(tan(k_ArrivalAngle) + 2 * GetTargetDisp().y / GetTargetDisp().x);
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
    float LaunchAngle = ShotVAngle();
    return GetTargetDisp().x * (1 / cos(LaunchAngle)) * sqrt(k_GravityAccel / (2 * (GetTargetDisp().x * tan(LaunchAngle) - GetTargetDisp().y)));
}
