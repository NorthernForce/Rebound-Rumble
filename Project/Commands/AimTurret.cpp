#include "../Robotmap.h"
#include "AimTurret.h"

const double p = 0.2; //set this value
const double i = 0.0; //keep at zero
const double d = 0.0; //set this value

const double tolerance = 5; //tolerance in percent

const double maxAngle = 25; //range is +- maxAngle

AimTurret::AimTurret(): PIDCommand(p,i,d)
{
	Requires(CommandBase::s_camera);
	Requires(CommandBase::s_turret);
	
}

// Called just before this Command runs the first time
void AimTurret::Initialize() 
{
	this->_Initialize();
	PID_Controller = GetPIDController();
	PID_Controller->SetInputRange(-maxAngle, maxAngle);
	PID_Controller->SetOutputRange(-1,1);
	PID_Controller->SetTolerance(tolerance);
	SetSetpoint(0.0);
}

// Called repeatedly when this Command is scheduled to run
void AimTurret::Execute() 
{
	this->_Execute();
}

// Make this return true when this Command no longer needs to run execute()
bool AimTurret::IsFinished() 
{
	return false;
}

// Called once after isFinished returns true
void AimTurret::End() 
{
	this->_End();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimTurret::Interrupted() 
{
	this->_Interrupted();
}

double AimTurret::ReturnPIDInput()
{
	return CommandBase::s_camera->GetAngleToTarget();
}

void AimTurret::UsePIDOutput(double output)
{
	//printf("Using PID Output\n\r");
	//printf("Output: %f\n\r", output);
	if(!(PID_Controller->OnTarget()))
		CommandBase::s_turret->Turn(output);
}
