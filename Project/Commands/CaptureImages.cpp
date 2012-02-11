#include "CaptureImages.h"

CaptureImages::CaptureImages() :
	CommandBase ("CaptureImages")
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
    // We don't want to require the camera subsystem because
    // otherwise, nothing else could use the subsystem as this
    // command is running all the time.
}

// Called just before this Command runs the first time
void CaptureImages::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void CaptureImages::Execute() {
	s_camera->CaptureImages(k_ImageCaptureCount);
    printf("Capturing %i images . . .",k_ImageCaptureCount);
}

// Make this return true when this Command no longer needs to run execute()
bool CaptureImages::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CaptureImages::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CaptureImages::Interrupted() {
}
