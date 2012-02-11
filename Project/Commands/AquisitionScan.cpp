#include "AquisitionScan.h"
#include "CameraMount.h"
#include "Camera.h"

AquisitionScan::AquisitionScan() : CommandBase("AquisitionScan")
{
	// Use requires() here to declare subsystem dependencies

}

// Called just before this Command runs the first time
void AquisitionScan::Initialize() 
{
	int initAngle = 0;
	int angleToTarget = 0;
	int distanceToTarget = 0;
}

// Called repeatedly when this Command is scheduled to run
void AquisitionScan::Execute() 
{
	
		Tilt(22/28); //in radians pi/4 = 45 degrees
		
		if (GetPanAngle()<(22/7)){ //in radians pi = 180 degrees
			
			inittAngle = initAngle + (22/1260); // in radians pi/180  = 1 degrees
			
			if(HasTarget()){
				Wait(.05);
				angleToTarget = GetAngleToTarget();
				Pan(angleToTarget);
				Wait(.05);
				IsFinished = true;
			}
			
		}
		
		else {
			Pan(0);
		}
}

// Make this return true when this Command no longer needs to run execute()
bool AquisitionScan::IsFinished() 
{
	return false;
}

// Called once after isFinished returns true
void AquisitionScan::End() 
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AquisitionScan::Interrupted() 
{
	
}
