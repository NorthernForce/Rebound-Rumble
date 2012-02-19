/*
 * RampManipulator.cpp
 *
 *  Created on: Feb 19, 2012
 *      Author: Mike
 */

#include "RampManipulator.h"

/*
 * Default constructor
 */
RampManipulator::RampManipulator( int RelayPort, int SolonoidPort) 
: Subsystem("Drive"),
m_RampManipulatorMotor(RelayPort),
m_RampManipulatorSoleniod(SolonoidPort)
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
	m_RampManipulatorSoleniod.Set(0);
}

void RampManipulator::ReleaseLock()
{
	m_RampManipulatorSoleniod.Set(1);
}
