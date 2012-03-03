#include "ShootBall.h"

ShootBall::ShootBall(): CommandBase("ShootBall") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_ballLifter);
Requires(s_ballShooter);		
}

// Called just before this Command runs the first time
void ShootBall::Initialize() {
	s_ballShooter->SetSpeed(1.0);
}

// Called repeatedly when this Command is scheduled to run
void ShootBall::Execute() {
	// Wait 25 cycles before we. enable the lift
	if (TimeSinceInitialized() > 2)
		s_ballLifter->EnableLift();
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBall::IsFinished() {
//	return s_ballLifter->GetLimit();
	return false;
}

// Called once after isFinished returns true
void ShootBall::End() {
	s_ballLifter->DisableLift();
	s_ballShooter->SetSpeed(.2);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootBall::Interrupted() {
	s_ballLifter->DisableLift();
	s_ballShooter->SetSpeed(.2);
}
