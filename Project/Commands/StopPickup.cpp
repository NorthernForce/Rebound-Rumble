#include "StopPickup.h"

StopPickup::StopPickup(): CommandBase("StopPickup") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_ballPickup);
}

// Called just before this Command runs the first time
void StopPickup::Initialize() {
	s_ballPickup->Stop();
}

// Called repeatedly when this Command is scheduled to run
void StopPickup::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool StopPickup::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void StopPickup::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopPickup::Interrupted() {
}
