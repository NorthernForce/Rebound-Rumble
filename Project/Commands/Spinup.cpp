#include "Spinup.h"
#include <math.h>

Spinup::Spinup(): CommandBase("Spinup"), velocity(0) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_ballShooter);
}

// Called just before this Command runs the first time
void Spinup::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Spinup::Execute() {
	float targetDist = s_camera->GetHorizontalDistance();
	velocity = targetDist * k_secTheta * sqrt(k_GravityAccel / (2 * (targetDist * k_tanTheta - k_targetHeight)));
	s_ballShooter->SetSpeed(velocity);
}

// Make this return true when this Command no longer needs to run execute()
bool Spinup::IsFinished() {
	Vector2D speed = s_ballShooter->GetSpeed();
	return ( (speed.x < velocity + k_spinupTolerance) && 
			 (speed.x > velocity - k_spinupTolerance) && 
			 (speed.y < velocity + k_spinupTolerance) && 
			 (speed.y > velocity - k_spinupTolerance) );
}

// Called once after isFinished returns true
void Spinup::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Spinup::Interrupted() {
}
