#include "TurnTurretRight.h"

TurnTurretRight::TurnTurretRight() : 
CommandBase("TurnTurretRight")
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_turret);
}

// Called just before this Command runs the first time
void TurnTurretRight::Initialize() {
	
}
 
// Called repeatedly when this Command is scheduled to run
void TurnTurretRight::Execute() {
	s_turret->SetPosition(s_turret->GetPosition()+.1);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnTurretRight::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TurnTurretRight::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnTurretRight::Interrupted() {

}
