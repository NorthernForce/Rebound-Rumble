#include "BallPickup.h"
#include "../Robotmap.h"
#include "../Commands/StartPickup.h"

BallPickup::BallPickup() : 
	Subsystem("BallPickup"),
	m_pickupMotor(k_pickupMotorRelay, Relay::kBothDirections)
{

}
    
void BallPickup::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new StartPickup());
}

void BallPickup::Start()
{
	m_pickupMotor.Set(Relay::kForward);
}

void BallPickup::Stop()
{
	m_pickupMotor.Set(Relay::kOff);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
