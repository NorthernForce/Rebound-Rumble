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
	s_RampManipulator->MotorForward();
	s_RampManipulator->ReleaseLock();
	_state = 0;
	printf("Raise: State 0\n\r");
}

// Called repeatedly when this Command is scheduled to run
void RaiseRampManipulator::Execute() 
{
	if (s_RampManipulator->m_down)
	{
		if (_state == 0 && TimeSinceInitialized() > .1 )
		{
			s_RampManipulator->MotorBackward();
			_state = 1;
			printf("Raise: State 1\n\r");
		}
		if (_state == 1 && TimeSinceInitialized() > .6 )
		{
			s_RampManipulator->MotorStop();
			_state = 2;
			printf("Raise: State 2\n\r");
			s_RampManipulator->m_down = false;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseRampManipulator::IsFinished() {
	return (_state == 2);
}

// Called once after isFinished returns true
void RaiseRampManipulator::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseRampManipulator::Interrupted() {
}
