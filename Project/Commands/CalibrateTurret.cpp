#include "CalibrateTurret.h"

CalibrateTurret::CalibrateTurret(): CommandBase("CalibrateTurret") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_turret);
}

// Called just before this Command runs the first time
void CalibrateTurret::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void CalibrateTurret::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool CalibrateTurret::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CalibrateTurret::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CalibrateTurret::Interrupted() {
}
