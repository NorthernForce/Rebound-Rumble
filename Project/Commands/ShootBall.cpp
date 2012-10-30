#include "ShootBall.h"

ShootBall::ShootBall(): CommandBase("ShootBall") {
	Requires(s_ballLifter);
	Requires(s_ballShooter);		
}

// Called just before this Command runs the first time
void ShootBall::Initialize() {
	s_ballShooter->SetSpeed(0.35);
	s_ballLifter->EnableLift();

}

// Called repeatedly when this Command is scheduled to run
void ShootBall::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBall::IsFinished() {
	if (TimeSinceInitialized() >= 1 && s_ballLifter->GetLimit())
		return true;
	else
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
