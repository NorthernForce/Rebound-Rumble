#include "../Robotmap.h"
#include "AimTurretPID.h"

namespace
{
	const double p = 1.0; //set this value
	const double i = 0.06; //keep at zero
	const double d = 10.0; //set this value

	const double tolerance = 2; //tolerance in percent
}

AimTurretPID::AimTurretPID(): PIDCommand(p,i,d)
{
	Requires(CommandBase::s_camera);
	Requires(CommandBase::s_turret);
}

// Called just before this Command runs the first time
void AimTurretPID::Initialize()
{
	this->_Initialize();
	PIDController& PID_Controller = *GetPIDController();
	PID_Controller.SetInputRange(-0.4, 0.4);
	PID_Controller.SetOutputRange(-1,1);
	PID_Controller.SetTolerance(tolerance);
	SetSetpoint(0.0);
}

/**
 * @brief Aims the turret.
 */
void AimTurretPID::Execute()
{
	if (CommandBase::s_camera->HasTarget())
		_Execute();
}

// Make this return true when this Command no longer needs to run execute()
bool AimTurretPID::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AimTurretPID::End()
{
	this->_End();
	CommandBase::s_turret->SetPosition(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimTurretPID::Interrupted()
{
	this->_Interrupted();
	CommandBase::s_turret->SetPosition(0.0);
}

double AimTurretPID::ReturnPIDInput()
{
	return CommandBase::s_camera->GetAngleToTarget();
}

void AimTurretPID::UsePIDOutput(double output)
{
	//printf("Using PID Output\n\r");
	//printf("Output: %f\n\r", output);
	CommandBase::s_turret->SetPosition(output);
}
