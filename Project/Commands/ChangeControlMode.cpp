#include "ChangeControlMode.h"

ChangeControlMode::ChangeControlMode(bool usingEncoders):
	CommandBase("ChangeControlMode")
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	m_usingEncoders = usingEncoders;
}

// Called just before this Command runs the first time
void ChangeControlMode::Initialize() 
{
	
}

// Called repeatedly when this Command is scheduled to run
void ChangeControlMode::Execute() 
{
	s_drive->ChangeControlMode(m_usingEncoders);
}

// Make this return true when this Command no longer needs to run execute()
bool ChangeControlMode::IsFinished() 
{
	return true;
}

// Called once after isFinished returns true
void ChangeControlMode::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ChangeControlMode::Interrupted() 
{
	
}
