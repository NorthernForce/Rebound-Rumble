#include "AimTurret.h"

static const float k_tolerance = 1.0f; // TODO: set this to a good value

AimTurret::AimTurret() : CommandBase("AimTurret") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void AimTurret::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void AimTurret::Execute() {
	angle = s_camera->GetAngleToTarget();
	s_turret->TurnTurret(angle);
}

// Make this return true when this Command no longer needs to run execute()
bool AimTurret::IsFinished() {
	return ( (angle < s_turret->GetAngle() + k_tolerance) &&
			 (angle > s_turret->GetAngle() - k_tolerance) );
}

// Called once after isFinished returns true
void AimTurret::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimTurret::Interrupted() {
}
