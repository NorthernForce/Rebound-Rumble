/*
 * RampManipulator.cpp
 *
 *  Created on: Feb 19, 2012
 *      Author: Mike
 */

#include "RampManipulator.h"
#include "../Robotmap.h"

namespace
{
	const float k_RightLockAngle = 1.0;
	const float k_RightUnlockAngle = 0.6;
	const float k_LeftLockAngle = 0.0;
	const float k_LeftUnlockAngle = 0.4;
}

/*
 * Default constructor
 */
RampManipulator::RampManipulator() : 
		Subsystem("RampManipulator"),
		m_down(false),
		m_RampManipulatorMotorRight(k_rampManipulatorRelayRight,Relay::kBothDirections),
		m_RampManipulatorMotorLeft(k_rampManipulatorRelayLeft, Relay::kBothDirections),
		m_LeftLockServo(k_LeftServoPort),
		m_RightLockServo(k_RightServoPort)
{
}


/**
 * @brief Sets up the default command for the subsystem.
 */
void RampManipulator::InitDefaultCommand() 
{
}

void RampManipulator::MoveRampDown()
{
	m_RampManipulatorMotorRight.Set(Relay::kReverse);
	m_RampManipulatorMotorLeft.Set(Relay::kReverse);
}

void RampManipulator::MoveRampUp()
{
	m_RampManipulatorMotorRight.Set(Relay::kForward);
	m_RampManipulatorMotorLeft.Set(Relay::kForward);
}

void RampManipulator::MotorStop()
{
	m_RampManipulatorMotorRight.Set(Relay::kOff);
	m_RampManipulatorMotorLeft.Set(Relay::kOff);
}

void RampManipulator::EngageLock()
{
	m_LeftLockServo.Set(k_LeftLockAngle);
	m_RightLockServo.Set(k_RightLockAngle);
}

void RampManipulator::ReleaseLock()
{
	m_LeftLockServo.Set(k_LeftUnlockAngle);
	m_RightLockServo.Set(k_RightUnlockAngle);
}
