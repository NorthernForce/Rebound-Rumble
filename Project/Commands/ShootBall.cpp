#include "ShootBall.h"

ShootBall::ShootBall() : CommandBase("ShootBall") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void ShootBall::Initialize() {
	SetTimeout(0.5);
}

// Called repeatedly when this Command is scheduled to run
void ShootBall::Execute() {
	s_ballShooter->Fire();
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBall::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void ShootBall::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootBall::Interrupted() {
}
