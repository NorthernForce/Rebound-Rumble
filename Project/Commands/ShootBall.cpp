#include "ShootBall.h"

ShootBall::ShootBall(): CommandBase("ShootBall") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	if(s_ballLifter) Requires(s_ballLifter);
	if(s_ballShooter) Requires(s_ballShooter);
	m_ballsToShoot = 0;
}

ShootBall::ShootBall(int num): CommandBase("ShootBall")
{
	if (s_ballLifter) Requires(s_ballLifter);
	if (s_ballShooter) Requires(s_ballShooter);
	m_ballsToShoot = num;
}

// Called just before this Command runs the first time
void ShootBall::Initialize() {
	if(s_ballShooter) s_ballShooter->SetSpeed(1.0);
}

// Called repeatedly when this Command is scheduled to run
void ShootBall::Execute() {
	// Wait 25 cycles before we. enable the lift
	if (TimeSinceInitialized() > 2)
	{
		if (s_ballLifter) s_ballLifter->EnableLift();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShootBall::IsFinished() {
//	return s_ballLifter->GetLimit();
	if ( (m_ballsToShoot != 0) && (TimeSinceInitialized() > 3*m_ballsToShoot)) {
		return true;
	} else return false;
}

// Called once after isFinished returns true
void ShootBall::End() {
	if(s_ballLifter) s_ballLifter->DisableLift();
	if(s_ballShooter) s_ballShooter->SetSpeed(.2);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootBall::Interrupted() {
	if(s_ballLifter) s_ballLifter->DisableLift();
	if(s_ballShooter) s_ballShooter->SetSpeed(.2);
}
