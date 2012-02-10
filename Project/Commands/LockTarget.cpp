#include "LockTarget.h"

LockTarget::LockTarget() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_turret);
}

// Called just before this Command runs the first time
void LockTarget::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void LockTarget::Execute() {
	if(s_camera->HasTarget())
	s_turret->TurnTurret(s_camera->GetAngleToTarget());
}

// Make this return true when this Command no longer needs to run execute()
bool LockTarget::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LockTarget::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LockTarget::Interrupted() {
}
