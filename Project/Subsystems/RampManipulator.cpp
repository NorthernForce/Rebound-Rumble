/*
 * RampManipulator.cpp
 *
 *  Created on: Feb 19, 2012
 *      Author: Mike
 */

#include "RampManipulator.h"

const int k_LeftLockAngle = 10;
const int k_LeftUnlockAngle = 10;
const int k_RightLockAngle = 10;
const int k_RightUnlockAngle = 10;

/*
 * Default constructor
 */
RampManipulator::RampManipulator( int RelayPort, int LeftServoPort, int RightServoPort ) 
: Subsystem("RampManipulator"),
m_RampManipulatorMotor(RelayPort),
m_LeftLockServo(LeftServoPort),
m_RightLockServo(RightServoPort)
//m_RampManipulatorSoleniod(SolonoidPort)
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
//	m_RampManipulatorSoleniod.Set(0);
}

void RampManipulator::ReleaseLock()
{
	m_LeftLockServo.SetAngle(k_LeftUnlockAngle);
	m_RightLockServo.SetAngle(k_RightUnlockAngle);
//	m_RampManipulatorSoleniod.Set(1);
}
