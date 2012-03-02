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
		s_RampManipulator->MoveRampDown();
		s_RampManipulator->ReleaseLock();
		_state = RaiseRamps;
	} else {
		_state = Complete;
	}
}

// Called repeatedly when this Command is scheduled to run
void RaiseRampManipulator::Execute() 
{
	if (_state == RaiseRamps && TimeSinceInitialized() > .15 )
	{
		s_RampManipulator->MoveRampUp();
		_state = StopMotors;
	}
	if (_state == StopMotors && TimeSinceInitialized() > .65 )
	{
		s_RampManipulator->MotorStop();
		_state = WaitForStop;
	}
	if (_state == WaitForStop && TimeSinceInitialized() >.66)
	{
		s_RampManipulator->m_down = false;
		_state = Complete;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseRampManipulator::IsFinished() {
	return (_state == Complete);
}

// Called once after isFinished returns true
void RaiseRampManipulator::End() {
	s_RampManipulator->MotorStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseRampManipulator::Interrupted() {
	s_RampManipulator->MotorStop();
}
