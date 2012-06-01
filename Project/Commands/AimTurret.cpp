#include "AimTurret.h"
#include "../Robotmap.h"

AimTurret::AimTurret() : CommandBase("AimTurret") 
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_turret);
	Requires(s_camera);
}

// Called just before this Command runs the first time
void AimTurret::Initialize() 
{
	// s_turret->Calibrate();
}

// Called repeatedly when this Command is scheduled to run
void AimTurret::Execute() 
{
	// if (!s_turret->m_calibrated)
	// {
	// 	s_turret->Calibrate();
	// }
	// else if (s_turret->m_calibrated)
	// {
	// 	if (s_camera->HasTarget() && k_track == true) {
	// 		if (oi->GetManipulatorStick().GetYButton() || oi->GetStick().GetYButton())
	// 			s_turret->SetPosition(k_turretCenter);
	// 		else
	// 			s_turret->SetPosition(s_camera->GetTurretSetpoint());
	// 	} else {
	// 		if (oi->GetManipulatorStick().GetBButton())
	// 			s_turret->SetPosition(s_turret->GetPosition()+.05);
	// 		else if (oi->GetManipulatorStick().GetXButton())
	// 			s_turret->SetPosition(s_turret->GetPosition()-.05);
	// 		else if (oi->GetManipulatorStick().GetYButton())
	// 			s_turret->SetPosition(k_turretCenter);
	// 	}
	// }
}

// Make this return true when this Command no longer needs to run execute()
bool AimTurret::IsFinished() 
{
	return false;
}

// Called once after isFinished returns true
void AimTurret::End() 
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimTurret::Interrupted() 
{
	s_turret->SetPosition(k_turretCenter);
}
