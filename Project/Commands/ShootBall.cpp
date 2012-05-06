#include "ShootBall.h"

ShootBall::ShootBall(): CommandBase("ShootBall") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_ballLifter);
Requires(s_ballShooter);		
}

// Called just before this Command runs the first time
void ShootBall::Initialize() {
	if (fabs(oi->GetManipulatorStick().GetRawAxis(3)) < 0.5 )
		s_ballShooter->SetSpeed(0.5);
	else
		s_ballShooter->SetSpeed(fabs(oi->GetManipulatorStick().GetRawAxis(3)));
	s_ballLifter->EnableLift();

}

// Called repeatedly when this Command is scheduled to run
void ShootBall::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBall::IsFinished() {
	if (TimeSinceInitialized() >= 4.5 && s_ballLifter->GetLimit())
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void ShootBall::End() {
	s_ballLifter->DisableLift();
	s_ballShooter->SetSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootBall::Interrupted() {
	s_ballLifter->DisableLift();
	s_ballShooter->SetSpeed(0);
}
