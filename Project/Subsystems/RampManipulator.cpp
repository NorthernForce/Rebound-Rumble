/*
 * RampManipulator.cpp
 *
 *  Created on: Feb 19, 2012
 *      Author: Mike
 */

#include "RampManipulator.h"
#include "../Robotmap.h"

const float k_LeftLockAngle = 0.5;
const float k_LeftUnlockAngle = 0.0;
const float k_RightLockAngle = 0.5;
const float k_RightUnlockAngle = 0.0;

/*
 * Default constructor
 */
RampManipulator::RampManipulator() : 
		Subsystem("RampManipulator"),
		m_RampManipulatorMotor(k_rampManipulatorRelay,Relay::kBothDirections),
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

void RampManipulator::MotorForward()
{
	m_RampManipulatorMotor.Set(Relay::kForward);
}

void RampManipulator::MotorBackward()
{
	m_RampManipulatorMotor.Set(Relay::kReverse);
}

void RampManipulator::MotorStop()
{
	m_RampManipulatorMotor.Set(Relay::kOff);
}

void RampManipulator::EngageLock()
{
	m_LeftLockServo.SetAngle(k_LeftLockAngle);
	m_RightLockServo.SetAngle(k_RightLockAngle);
}

void RampManipulator::ReleaseLock()
{
	m_LeftLockServo.SetAngle(k_LeftUnlockAngle);
	m_RightLockServo.SetAngle(k_RightUnlockAngle);
}

void RampManipulator::SetServo(float position)
{
	
}
