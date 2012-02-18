#include "BallPickup.h"
#include "../Robotmap.h"

/**
 * @brief Constructor for the ball pickup system.
 * I'm using the comma operator when initializing the jaguar
 * to provide feedback, as Steve did in BSBotDrive.cpp
 * 
 * @author Joseph Martin
 */
BallPickup::BallPickup() :
    Subsystem("BallPickup"),
    m_hasBall(false),
    m_pickupRelay((printf("Initializing pickup motor jaguar. \n"), k_pickupMotorRelay)) 
{
}
    
/**
 * @brief Sets the default command for the subsystem.
 */
void BallPickup::InitDefaultCommand() {
    // This subsystem technically has no default command because its
    // "default" command is also the default command of BallShooter.
}

/**
 * @brief Starts the motors for the ball pickup
 * system.
 * We should probably ramp this in the future.
 */
void BallPickup::Start()
{
	m_pickupRelay.Set(Relay::kOff);
}

/**
 * @brief Sends the ball currently in the pickup system to the
 * ball storage system.
 */
void BallPickup::AdvanceBall()
{
    return; // Not implemented
}

/**
 * @brief Stops the subsystem from picking up balls.
 * This will be called when we have a ball in the system.
 * We should probably ramp this in the future.
 */
void BallPickup::Stop()
{
	m_pickupRelay.Set(Relay::kOff);
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
	return m_hasBall;
}
