#include "ManualShoot.h"

ManualShoot::ManualShoot(): CommandBase("ManualShoot") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_ballShooter);
	Requires(s_turret);
}

// Called just before this Command runs the first time
void ManualShoot::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void ManualShoot::Execute() {
	XboxJoystick& controller = oi->GetManipulatorStick();
	s_turret->Turn(controller.GetRawAxis (4));
	s_ballShooter->SetSpeed(-controller.GetRawAxis(Joystick::kDefaultYAxis));
}

// Make this return true when this Command no longer needs to run execute()
bool ManualShoot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ManualShoot::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualShoot::Interrupted() {
}
