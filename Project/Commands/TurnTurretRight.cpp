#include "TurnTurretRight.h"

TurnTurretRight::TurnTurretRight() : 
CommandBase("TurnTurretRight")
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void TurnTurretRight::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void TurnTurretRight::Execute() {
	//if (CommandBase::s_camera->HasTarget())
	/*{
		if(s_camera->GetAngleToTarget()>3)
			CommandBase::s_turret->Turn(0.12);
		if(s_camera->GetAngleToTarget()<3)
			CommandBase::s_turret->Turn(-.12);
	}
	else*/
		CommandBase::s_turret->Turn(.25);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnTurretRight::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TurnTurretRight::End() {
	CommandBase::s_turret->Turn(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnTurretRight::Interrupted() {
	CommandBase::s_turret->Turn(0);
}
