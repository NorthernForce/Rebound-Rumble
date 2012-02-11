#include "AquisitionScan.h"
#include "../CommandBase.h"

AquisitionScan::AquisitionScan() : 
	CommandBase("AquisitionScan"),
	m_rateOfChange(0),
	m_angleToTarget(0),
	m_initAngle(0),
	m_finished(false)
{
	// Use requires() here to declare subsystem dependencies

}

// Called just before this Command runs the first time
void AquisitionScan::Initialize()
{
	m_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void AquisitionScan::Execute() 
{
	
		s_cameraMount->Tilt(22.0/28.0); //in radians pi/4 = 45 degrees
		if (m_rateOfChange == 0){
			
			m_initAngle = m_initAngle + (22.0/1260.0); // in radians pi/180  = 1 degrees
			
			if(s_camera->HasTarget()){
				Wait(.05);
				m_angleToTarget = s_camera->GetAngleToTarget();
				Wait(.05);
				s_cameraMount->Pan(m_angleToTarget);
				m_finished = true;
			}
			if(m_initAngle == 1){
				m_rateOfChange = 1;
			}
			
		}
		
		else {
			
			m_initAngle = m_initAngle - (22/1260); // in radians pi/180  = 1 degrees
						
						if(s_camera->HasTarget()){
							Wait(.05);
							m_angleToTarget = s_camera->GetAngleToTarget();
							s_cameraMount->Pan(m_angleToTarget);
							Wait(.05);
							m_finished = true;
						}
						if(m_initAngle == 0){
							m_rateOfChange = 0;
						}
			
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
