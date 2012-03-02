#include "ReversePickup.h"

ReversePickup::ReversePickup(): CommandBase("ReversePickup") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_ballPickup);
}

// Called just before this Command runs the first time
void ReversePickup::Initialize() {
	s_ballPickup->Reverse();
}

// Called repeatedly when this Command is scheduled to run
void ReversePickup::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ReversePickup::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ReversePickup::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReversePickup::Interrupted() {
	s_ballPickup->Stop();
}
