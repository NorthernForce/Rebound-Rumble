#include "Spinup.h"
#include <math.h>

static const float k_secTheta = 2;//1/cos(M_PI/3);
static const float k_tanTheta = sqrt(3.0f);//tan(M_PI/3);
static const float k_tolerance = 1;

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
	velocity = GetTargetDisp().x * k_secTheta * sqrt(k_GravityAccel / (2 * (GetTargetDisp().x * k_tanTheta - GetTargetDisp().y)));
	s_ballShooter->SetSpeed(velocity);
}

// Make this return true when this Command no longer needs to run execute()
bool Spinup::IsFinished() {
	Vector2D speed = s_ballShooter->GetSpeed();
	return ( (speed.x < velocity + k_tolerance) && 
			 (speed.x > velocity - k_tolerance) && 
			 (speed.y < velocity + k_tolerance) && 
			 (speed.y > velocity - k_tolerance) );
}

// Called once after isFinished returns true
void Spinup::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Spinup::Interrupted() {
}

Vector3D Spinup::GetTargetDisp(){
	return Vector3D();
}
