#include "AquisitionScan.h"
#include "../CommandBase.h"

AquisitionScan::AquisitionScan() :
	CommandBase("AquisitionScan"),
	m_rateOfChange(0),
	m_angleToTarget(0),
	m_camAngle(0),
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
		s_cameraMount->Tilt(M_PI/4); //in radians pi/4 = 45 degrees
		if (m_rateOfChange == 0){

			m_camAngle = m_camAngle + (22.0/1260.0); // in radians pi/180  = 1 degrees

			Wait(.1);

			if(s_camera->HasTarget()){

				m_angleToTarget = s_camera->GetAngleToTarget();

				s_cameraMount->Pan((m_angleToTarget)+(m_camAngle));
				m_finished = true;
			}
			if(m_camAngle == 1){
				m_rateOfChange = 1;
			}

		}

		else {

			m_camAngle = m_camAngle - (22.0/1260.0); // in radians pi/180  = 1 degrees

			Wait(.1);
						if(s_camera->HasTarget()){

							m_angleToTarget = s_camera->GetAngleToTarget();
							s_cameraMount->Pan((m_angleToTarget)+(m_camAngle));
							m_finished = true;
						}
						if(m_camAngle == 0){
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
