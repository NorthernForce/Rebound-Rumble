#include "LowerRampManipulator.h"

LowerRampManipulator::LowerRampManipulator() : CommandBase("LowerRampManipulator")
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	if(s_RampManipulator) Requires(s_RampManipulator);
}

// Called just before this Command runs the first time
void LowerRampManipulator::Initialize() {
	if (s_RampManipulator == 0 || s_RampManipulator->m_down)
	{
		_state = Complete;
	} else {
		s_RampManipulator->ReleaseLock();
		s_RampManipulator->MoveRampDown();
		_state = StopMotors;
	}
}

// Called repeatedly when this Command is scheduled to run
void LowerRampManipulator::Execute()
{
	if (_state == StopMotors && TimeSinceInitialized() > .7)
	{
		if(s_RampManipulator) s_RampManipulator->MotorStop();
		_state = EngageLock;
	}
	if (_state == EngageLock && TimeSinceInitialized() >.8)
	{
		if(s_RampManipulator) s_RampManipulator->EngageLock();
		_state = BackOffMotors;
	}
	if (_state == BackOffMotors && TimeSinceInitialized() >.9)
	{
		if(s_RampManipulator) s_RampManipulator->MoveRampUp();
		_state = StopBackOff;
	}
	if (_state == StopBackOff && TimeSinceInitialized() >1.5)
	{
		if(s_RampManipulator) s_RampManipulator->MotorStop();
		_state = WaitForStop;
	}
	if (_state == WaitForStop && TimeSinceInitialized() > .76)
	{
		if(s_RampManipulator) s_RampManipulator->m_down = true;
		_state = Complete;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LowerRampManipulator::IsFinished() {
	return (_state == Complete);
}

// Called once after isFinished returns true
void LowerRampManipulator::End() {
	if(s_RampManipulator) s_RampManipulator->MotorStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerRampManipulator::Interrupted() {
	if(s_RampManipulator) s_RampManipulator->MotorStop();
}
