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
Vector3D Targeting::GetTargetDisp()
{
    return Vector3D(); 
}

/**
 * @brief Initializes the default command for the subsystem.
 */
void Targeting::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


/**
 * @brief Gets the speed and horizontal and vertical angle the ball 
 * needs to go to make the shot.
 * 
 * @return The speed, in voltage.
 */
Aim Targeting::GetAim()
{
    float angle = atan(tan(k_ArrivalAngle) + 2 * GetTargetDisp().y / GetTargetDisp().x);
    float velocity = GetTargetDisp().x * (1 / cos(angle)) * sqrt(k_GravityAccel / (2 * (GetTargetDisp().x * tan(angle) - GetTargetDisp().y)));
    return Aim(0.0,angle,velocity);
}
