#include "DriveToRamp.h"

namespace
{
	static const float k_minTime = 2;
	static const float k_maxTime = 3;
}

DriveToRamp::DriveToRamp() : CommandBase("DriveToRamp") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	if(s_drive)
	{
		Requires(s_drive);
	}
}

// Called just before this Command runs the first time
void DriveToRamp::Initialize() {
	count = 0;
	finished = false;
	if(s_drive)
	{
		s_drive->DriveRobot(0.5, 0.0); // Drives half speed
	}
}

// Called repeatedly when this Command is scheduled to run
void DriveToRamp::Execute() {
	
	float angle = acos(Limit(CommandBase::s_accelerometer->GetAccelerations().z, 1)) * 180/M_PI;
	if(angle > 15) 
	{
		printf("Angle: %f", angle);
		count++;
		if( (count > 3) && (TimeSinceInitialized() > k_minTime) ) finished = true;
	} else
	{
		count = 0;
	}
//	printf("Angle: %f\n count: %d\n", angle, count);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToRamp::IsFinished() {
	return (finished || (TimeSinceInitialized() > k_maxTime)); // until we hit the ramp
}

// Called once after isFinished returns true
void DriveToRamp::End() {
	printf("Hit Ramp\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToRamp::Interrupted() {
}

float DriveToRamp::Limit(float input, float max)
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

