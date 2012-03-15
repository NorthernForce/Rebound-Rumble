#include "CalibrateTurret.h"

CalibrateTurret::CalibrateTurret(): CommandBase("CalibrateTurret") 
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_turret);
}

// Called just before this Command runs the first time
void CalibrateTurret::Initialize() 
{
	s_turret->SetMaxVoltage(6.0);
	s_turret->EnableControl(0.0);
	s_turret->SetPosition(-3);
	
}

// Called repeatedly when this Command is scheduled to run
void CalibrateTurret::Execute() 
{
	s_turret->SetPosition(-3);
}

// Make this return true when this Command no longer needs to run execute()
bool CalibrateTurret::IsFinished() 
{
	return (TimeSinceInitialized() > 2);
}

// Called once after isFinished returns true
void CalibrateTurret::End() 
{
	s_turret->EnableControl(0.0);
	s_turret->SetMaxVoltage(k_driveMaxOutputVoltage);
	s_turret->SetPosition(k_turretCenter);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CalibrateTurret::Interrupted() 
{

}
