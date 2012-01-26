#include "BallPickup.h"
#include "../Robotmap.h"

/**
 * @brief Constructor for the ball pickup system.
 * 
 * @author Arthur Lockman
 */
BallPickup::BallPickup() : Subsystem("BallPickup") {
	
}
    
/**
 * @brief Sets the default command for the subsystem.
 */
void BallPickup::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Spins up the motors for the ball pickup
 * system.
 * 
 * @author Arthur Lockman
 */
void BallPickup::Spinup()
{
	
}

/**
 * @brief Stops all motors in the pickup system
 * from running. Only used in emergency.
 * 
 * @author Arthur Lockman
 */
void BallPickup::Stop()
{
	
}

/**
 * @brief Figures out whether or not the ball pickup
 * system has a ball currently in it. 
 * 
 * @return A bool, whether or not the system is currently
 * holding a ball.
 */
bool BallPickup::HasBall()
{
	return false;
}
