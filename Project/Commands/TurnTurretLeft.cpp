#include "TurnTurretLeft.h"

TurnTurretLeft::TurnTurretLeft():
CommandBase("TurnTurretLeft")
{
	// Use requires() here to declare subsystem dependencies
	Requires(s_turret);
}

// Called just before this Command runs the first time
void TurnTurretLeft::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TurnTurretLeft::Execute() {
	s_turret->SetPosition(s_turret->GetPosition()-.1);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnTurretLeft::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TurnTurretLeft::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnTurretLeft::Interrupted() {
}
