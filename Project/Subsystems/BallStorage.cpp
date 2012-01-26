#include "BallStorage.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the Ball Storage system.
 */
BallStorage::BallStorage() : Subsystem("BallStorage") {
	
}
   
/**
 * @brief Sets up the default command for the robot.
 */
void BallStorage::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Gets the number of balls currently in the
 * robot.
 * 
 * @return An int, the number of balls.
 */
int CountBalls()
{
    return 0;
}

/**
 * @brief Stops the storage mechanism from moving.
 * Used to stop ball flow once a ball is collected.
 */
void Stop()
{
	
}

/**
 * @brief Advances the ball to a specified position
 * in the storage mechanism. It has three possible
 * positions: k_ballPosition1, k_ballPosition2, or k_ballPosition3.
 */
void AdvanceBall(int position)
{
	
}

/**
 * @brief Clears all the balls out of the storage mechanism.
 */
void Clear()
{
	
}
