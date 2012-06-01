#include "StopFiring.h"
#include "AimTurret.h"
#include "ShootBall.h"

StopFiring::StopFiring() : CommandBase("StopFiring"){
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void StopFiring::Initialize() {
 s_ballLifter->DisableLift();
	CommandBase::s_ballShooter->SetSpeed(0);
}

// Called repeatedly when this Command is scheduled to run
void StopFiring::Execute() {
	CommandBase::s_ballLifter->DisableLift();
	CommandBase::s_ballShooter->SetSpeed(0);
}

// Make this return true when this Command no longer needs to run execute()
bool StopFiring::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void StopFiring::End() {
	CommandBase::s_ballLifter->DisableLift();
	CommandBase::s_ballShooter->SetSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopFiring::Interrupted() {
	CommandBase::s_ballLifter->DisableLift();
	CommandBase::s_ballShooter->SetSpeed(0);
}
