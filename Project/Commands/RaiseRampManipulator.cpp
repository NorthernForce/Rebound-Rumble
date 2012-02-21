#include "RaiseRampManipulator.h"

RaiseRampManipulator::RaiseRampManipulator() : CommandBase("RaiseRampManipulator") 
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_RampManipulator);
}

// Called just before this Command runs the first time
void RaiseRampManipulator::Initialize() 
{
	if (s_RampManipulator->m_down)
	{
		_state = 3;
	} else {
		s_RampManipulator->MotorForward();
		s_RampManipulator->ReleaseLock();
		_state = 0;
	}
}

// Called repeatedly when this Command is scheduled to run
void RaiseRampManipulator::Execute() 
{
	if (_state == 0 && TimeSinceInitialized() > .1 )
	{
		s_RampManipulator->MotorBackward();
		_state = 1;
	}
	if (_state == 1 && TimeSinceInitialized() > .6 )
	{
		s_RampManipulator->MotorStop();
		_state = 2;
	}
	if (_state == 2 && TimeSinceInitialized() >.61)
	{
		s_RampManipulator->m_down = false;
		_state = 3;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseRampManipulator::IsFinished() {
	return (_state == 3);
}

// Called once after isFinished returns true
void RaiseRampManipulator::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseRampManipulator::Interrupted() {
}
