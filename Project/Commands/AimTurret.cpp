#include "../Robotmap.h"
#include "AimTurret.h"

namespace
{
	const double p = 1.0; //set this value
	const double i = 0.0; //keep at zero
	const double d = 0.0; //set this value

	const double tolerance = 3; //tolerance in percent
}

AimTurret::AimTurret(): PIDCommand(p,i,d)
{
	Requires(CommandBase::s_camera);
	Requires(CommandBase::s_turret);
}

// Called just before this Command runs the first time
void AimTurret::Initialize()
{
	this->_Initialize();
	PIDController& PID_Controller = *GetPIDController();
	PID_Controller.SetInputRange(-0.4, 0.4);
	PID_Controller.SetOutputRange(-0.3,0.3);
	PID_Controller.SetTolerance(tolerance);
	SetSetpoint(0.0);
}

/**
 * @brief Aims the turret.
 */
void AimTurret::Execute()
{
	if (CommandBase::s_camera->HasTarget())
		_Execute();
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
	CommandBase::s_turret->SetPosition(k_turretCenter);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimTurret::Interrupted()
{
	this->_Interrupted();
	CommandBase::s_turret->SetPosition(k_turretCenter);
}

double AimTurret::ReturnPIDInput()
{
	return CommandBase::s_camera->GetAngleToTarget();
}

void AimTurret::UsePIDOutput(double output)
{
	//printf("Using PID Output\n\r");
	//printf("Output: %f\n\r", output);
	CommandBase::s_turret->SetPosition(output);
}
