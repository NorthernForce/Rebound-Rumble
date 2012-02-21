#include "StartPickup.h"

StartPickup::StartPickup(): CommandBase("StartPickup") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_ballPickup);
}

// Called just before this Command runs the first time
void StartPickup::Initialize() {
	s_ballPickup->Start();
}

// Called repeatedly when this Command is scheduled to run
void StartPickup::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool StartPickup::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void StartPickup::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StartPickup::Interrupted() {
}
