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
	if (s_RampManipulator->m_down)
	{
		_state = 5;
	} else {
		s_RampManipulator->ReleaseLock();
		s_RampManipulator->MotorForward();
		_state = 0;
	}
}

// Called repeatedly when this Command is scheduled to run
void LowerRampManipulator::Execute() 
{
	if (_state == 0 && TimeSinceInitialized() > .5)
	{
		s_RampManipulator->MotorStop();
		_state = 1;
	}
	if (_state == 1 && TimeSinceInitialized() >.6)
	{
		s_RampManipulator->EngageLock();
		_state = 2;
	}
	if (_state == 2 && TimeSinceInitialized() >.7)
	{
		s_RampManipulator->MotorBackward();
		_state = 3;
	}
	if (_state == 3 && TimeSinceInitialized() >.8)
	{
		s_RampManipulator->MotorStop();
		_state = 4;
	}
	if (_state == 4 && TimeSinceInitialized() > .81)
	{
		s_RampManipulator->m_down = true;
		_state = 5;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LowerRampManipulator::IsFinished() {
	return (_state == 5);
}

// Called once after isFinished returns true
void LowerRampManipulator::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerRampManipulator::Interrupted() {
}
