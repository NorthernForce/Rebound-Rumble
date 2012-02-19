#include "LowerRampManipulator.h"

LowerRampManipulator::LowerRampManipulator() : CommandBase("LowerRampManipulator") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void LowerRampManipulator::Initialize() {
	//Advance the motor a bit to release pressure on the lock
	s_RampManipulator->MotorForward();
}

// Called repeatedly when this Command is scheduled to run
void LowerRampManipulator::Execute() {
	if (_state == 0 and TimeSinceInitialized() > 0.1)
	{
		//Stop the motor and release the lock.
		_state = 1;
		s_RampManipulator->MotorStop();
		s_RampManipulator->ReleaseLock();
	}
	if (_state == 1 and TimeSinceInitialized() > 0.4)
	{
		// Reverse the motor and wait for it to move back
		_state = 2;
		s_RampManipulator->MotorBackward();
	}
	if (_state == 2 and TimeSinceInitialized() > 1)
	{
		//Stop the motor and wait for it to stop
		_state = 3;
		s_RampManipulator->MotorStop();
	}
	if (_state == 3 and TimeSinceInitialized() > 1.1)
	{
		// Re-engage the lock.
		_state = 4;
		s_RampManipulator->EngageLock();
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
