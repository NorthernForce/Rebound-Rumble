#include "RaiseRampManipulator.h"

RaiseRampManipulator::RaiseRampManipulator() : CommandBase("RaiseRampManipulator") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void RaiseRampManipulator::Initialize() {
	_state = 0;
	s_RampManipulator->MotorForward();
}

// Called repeatedly when this Command is scheduled to run
void RaiseRampManipulator::Execute() {
	if (_state == 0 and TimeSinceInitialized() > 0.5)
	{
		_state = 1;
		s_RampManipulator->MotorStop();
	}
	if (_state == 1 and TimeSinceInitialized() > 0.7)
	{
		_state = 2;
		s_RampManipulator->MotorBackward();
	}
	if (_state == 2 and TimeSinceInitialized() > 0.8)
	{
		_state = 3;
		s_RampManipulator->MotorStop();
	}
	
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseRampManipulator::IsFinished() {
	return (_state = 3);
}

// Called once after isFinished returns true
void RaiseRampManipulator::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseRampManipulator::Interrupted() {
}
