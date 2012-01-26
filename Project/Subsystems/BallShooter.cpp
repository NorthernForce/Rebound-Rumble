#include "BallShooter.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the ball shooter.
 */
BallShooter::BallShooter() : Subsystem("BallShooter") {
	
}
    
/**
 * @brief Sets up the default command for the shooter.
 */
void BallShooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Adjusts the speed of the pitcher.
 * 
 * @param speed A float, the speed in voltage of the pitcher.
 * This should always be positive.
 */
void BallShooter::AdjustPitcherSpeed(float speed)
{
	
}

/**
 * @brief Sets the pitcher to spin at a set speed 
 * for startup.
 * 
 * @param speed A float, the speed in voltage of the pitcher.
 * This should always be positive.
 */
void BallShooter::Spinup(float speed)
{
	
}

/**
 * @brief Sets the vertical angle of the pitcher, relative
 * to the ground.
 * 
 * @param angle The angle to set it to, in degrees.
 */
void BallShooter::AdjustVerticalAngle(float angle)
{
	
}

/**
 * @brief Fires a ball.
 */
void BallShooter::Fire()
{
	
}
