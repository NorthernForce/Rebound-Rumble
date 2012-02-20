#include "Balance.h"
#include "../Robotmap.h"

const double p = 0.1; //set this value
const double i = 0.0; //keep at zero
const double d = 0.05; //set this value
const double maxAngle = M_PI/12;

Balance::Balance(): PIDCommand(p,i,d)
{
	Requires(CommandBase::s_drive);
	Requires(CommandBase::s_accelerometer);
	
}

// Called just before this Command runs the first time
void Balance::Initialize() 
{
	PIDCommand::_Initialize();
	SetSetpoint(0.0);
}

// Called repeatedly when this Command is scheduled to run
void Balance::Execute() 
{
	this->UsePIDOutput(this->ReturnPIDInput());
}

// Make this return true when this Command no longer needs to run execute()
bool Balance::IsFinished() 
{
		return false;
}

// Called once after isFinished returns true
void Balance::End() 
{
	PIDCommand::_End();
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Balance::Interrupted() 
{
	PIDCommand::_Interrupted();
}

double Balance::ReturnPIDInput()
{
	Vector3D accelerations = CommandBase::s_accelerometer->GetAccelerations();
	double returnVal = (acos(Limit(accelerations.z,1)) * sign(accelerations.y))/maxAngle;  
	printf("z-acceleration: %f\n\r", accelerations.z);
	printf("y-acceleration: %f\n\r", accelerations.y);
	printf("PIDInput: %f\n\r", returnVal);
	return returnVal;
}

void Balance::UsePIDOutput(double output)
{
	printf("Using PID Output\n\r");
	printf("Output: %f\n\r", output);
	double finalOutput = output*2;
	CommandBase::s_drive->DriveRobot((float)finalOutput, 0);
}


float Balance::sign(float number)
{
	if(number < 0)
		return -1;
	else
		return 1;
}

float Balance::Limit(float input, float max) 
{
    if (input > max)
    {
        return max;
    } else if (input < -max)
    {
        return -max;
    }
    return input;
}
