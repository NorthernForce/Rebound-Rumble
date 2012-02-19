#include "FollowRobot.h"


FollowRobot::FollowRobot():
CommandBase("FollowRobot") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void FollowRobot::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void FollowRobot::Execute() {
	if(CommandBase::s_ultrasonicSensor->GetRangeInInches()>k_followDistanceInches+1)
	s_drive->DriveRobot(.425,0);
	else if(CommandBase::s_ultrasonicSensor->GetRangeInInches()<k_followDistanceInches-1);
}

// Make this return true when this Command no longer needs to run execute()
bool FollowRobot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FollowRobot::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowRobot::Interrupted() {
}
