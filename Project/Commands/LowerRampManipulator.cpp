#include "LowerRampManipulator.h"

LowerRampManipulator::LowerRampManipulator() : CommandBase("LowerRampManipulator") 
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_RampManipulator);
}

// Called just before this Command runs the first time
void LowerRampManipulator::Initialize() {
	//Advance the motor a bit to release pressure on the lock
	s_RampManipulator->ReleaseLock();
	s_RampManipulator->MotorForward();
	_state = 0;
	printf("Lower: State 0\n\r");
}

// Called repeatedly when this Command is scheduled to run
void LowerRampManipulator::Execute() 
{
	if (s_RampManipulator->m_down)
	{
		
	} else if (!s_RampManipulator->m_down)
	{
		if (_state == 0 && TimeSinceInitialized() > .5)
		{
			s_RampManipulator->MotorStop();
			_state = 1;
			printf("Lower: State 1\n\r");
		}
		if (_state == 1 && TimeSinceInitialized() >.6)
		{
			s_RampManipulator->EngageLock();
			_state = 2;
			printf("Lower: State 2\n\r");
		}
		if (_state == 2 && TimeSinceInitialized() >.7)
		{
			s_RampManipulator->MotorBackward();
			_state = 3;
			printf("Lower: State 3\n\r");
		}
		if (_state == 3 && TimeSinceInitialized() >.8)
		{
			s_RampManipulator->MotorStop();
			_state = 4;
			printf("Lower: State 4\n\r");
			s_RampManipulator->m_down = true;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LowerRampManipulator::IsFinished() {
	return (_state == 4);
}

// Called once after isFinished returns true
void LowerRampManipulator::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerRampManipulator::Interrupted() {
}
