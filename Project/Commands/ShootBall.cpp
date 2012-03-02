#include "ShootBall.h"

ShootBall::ShootBall(): CommandBase("ShootBall") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_ballLifter);
}

// Called just before this Command runs the first time
void ShootBall::Initialize() {
	count=0;
	s_ballShooter->SetSpeed(.3);
//	s_ballPickup->Start();
	s_ballLifter->EnableLift();
}

// Called repeatedly when this Command is scheduled to run
void ShootBall::Execute() {
	if (s_ballLifter->GetLimit())
	{
		s_ballLifter->DisableLift();
		s_ballShooter->SetSpeed(0);
	}
		//s_ballShooter->SetSpeed(0);
	
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBall::IsFinished() {
	return s_ballLifter->GetLimit();
}

// Called once after isFinished returns true
void ShootBall::End() {
	s_ballLifter->DisableLift();
	//s_ballPickup->Stop();
	s_ballShooter->SetSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootBall::Interrupted() {
	s_ballLifter->DisableLift();
	//s_ballPickup->Stop();
	s_ballShooter->SetSpeed(0);
}
