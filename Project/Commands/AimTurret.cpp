#include "../Robotmap.h"
#include "AimTurret.h"

const double p = 0.2; //set this value
const double i = 0.0; //keep at zero
const double d = 0.0; //set this value

const double tolerance = 5; //tolerance in percent

const double maxAngle = 25; //range is +- maxAngle

const double scanSpeed = 0.1; //Speed to scan for a target if one isn't found.

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

/**
 * @brief Aims the turret. What this does at the moment is to 
 * aim the turret at the target if the camera sees a target. Otherwise,
 * it will scan back and forth slowly to help the camera find a target. 
 * THIS NEEDS TO BE TESTED.
 */
void AimTurret::Execute() 
{
	double time = 0.0;
	if (!(CommandBase::s_camera->HasTarget()))
	{
		time = TimeSinceInitialized();
		double _state = 0;
		
		if ( (TimeSinceInitialized() > time + 1) && (_state == 0) )
		{
			CommandBase::s_turret->Turn(-scanSpeed);
			CommandBase::s_drive->Feed();
			_state = 1;
		}
		if ( (TimeSinceInitialized() > time + 2) && (_state == 1) )
		{
			CommandBase::s_turret->Turn(scanSpeed);
			CommandBase::s_drive->Feed();
			_state = 0;
		}
	} 
	else if (CommandBase::s_camera->HasTarget())
	{
		this->_Execute();
	}
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
