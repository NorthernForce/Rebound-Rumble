#include "ParalellPark.h"

ParalellPark::ParalellPark():
	CommandBase("Autonomous")

{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void ParalellPark::Initialize() {
	time = TimeSinceInitialized();
	done = 0;
}

// Called repeatedly when this Command is scheduled to run
void ParalellPark::Execute() {
	
	if(done==0){
	
	while((TimeSinceInitialized() - time)==1000){
	s_drive->DriveRobot(-0.8,0);
	}
	
	time = TimeSinceInitialized();
	
	while((TimeSinceInitialized() - time)==1000){
	s_drive->DriveRobot(-0.5,0.4);
	}
	
	time = TimeSinceInitialized();
	
	while((TimeSinceInitialized() - time)==1000){
	s_drive->DriveRobot(-0.5,0);
	}
	
	time = TimeSinceInitialized();
	
	while((TimeSinceInitialized() - time)==1000){
	s_drive->DriveRobot(0,-0.4);
	}
	done = 1;
	
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ParalellPark::IsFinished() {
	
	if (done=1){
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void ParalellPark::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ParalellPark::Interrupted() {
}
