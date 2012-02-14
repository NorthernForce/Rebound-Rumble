#include "BallController.h"

BallController::BallController() : CommandBase("BallController") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
    Requires(s_ballPickup);
    Requires(s_ballStorage);
}

// Called just before this Command runs the first time
void BallController::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void BallController::Execute() 
{
    // If the ball pickup system has a ball, it should stop tyring to
    // pickup balls
//	if(s_ballPickup->HasBall()) 
//    {
//        s_ballPickup->Stop();
//        // If we have room in the ball storage system, put the ball there
//        if(s_ballStorage->CountBalls() < 2) 
//        {
//            s_ballStorage->GetBallFromPickup();
//        }
//    } else // Otherwise, start trying to pick up balls. 
//    {
//        s_ballPickup->Start();
//    }
}

// Make this return true when this Command no longer needs to run execute()
bool BallController::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void BallController::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallController::Interrupted() {
}
