#include <WPILib.h>
#include "CommandBase.h"

/**
 * @brief This class controls the entire robot,
 * everything it does, and all of its interactions
 * with the field, itself, and the operators.
 * 
 * @author Arthur Lockman
 */
class ReboundRumbleBot : public IterativeRobot 
{
public:
	ReboundRumbleBot() :
		m_autonomousCommand (0),
		m_dashboardCounter (0)
	{
	}

protected:
	virtual void RobotInit()
	{
		CommandBase::init();
		SmartDashboard::GetInstance()->init();
	}
	
	virtual void AutonomousInit() 
	{
		
	}
	
	virtual void AutonomousPeriodic() 
	{
		Scheduler::GetInstance()->Run();
		this->UpdateDashboard();
	}
	
	virtual void TeleopInit() 
	{
		if (m_autonomousCommand)
		{
			// This makes sure that the autonomous stops running when
			// teleop starts running. If you want the autonomous to 
			// continue until interrupted by another command, remove
			// this line or comment it out.
			m_autonomousCommand->Cancel();
		}
	}
	
	virtual void TeleopPeriodic() 
	{
		Scheduler::GetInstance()->Run();
		this->UpdateDashboard();
	}

	virtual void DisabledPeriodic()
	{
		this->UpdateDashboard();
	}

	/** @brief Updates the values on the dashboard
	 *
	 * @author Stephen Nutt
	 */
	void UpdateDashboard()
	{
		// Only update every 25 cycles (approx every 1/2 second)
		if ((++m_dashboardCounter % 25) != 0) return;

//		SmartDashboard& dashboard = *SmartDashboard::GetInstance();
		if (const Camera* const pCamera = CommandBase::s_camera)
		{
			const UINT32 time = pCamera->GetLastFrameProcessingTime();
			SetSmartDashboardDouble ("FPS", time ? 1000.0 / time : 0.0);
			SetSmartDashboardDouble ("Target Angle", pCamera->GetAngleToTarget());
		}
		
		if (const MaxbotixUltrasonic* const pUltrasonic = CommandBase::s_ultrasonicSensor)
		{
			SetSmartDashboardDouble ("Target Distance", pUltrasonic->GetRangeInInches() / 12.0);
		}
	}

private:

	/** @brief Updates a single double value on the dashboard, formatting
	 * the double nicely
	 *
	 * @author Stephen Nutt
	 */
	static void SetSmartDashboardDouble (const char* name, const double value)
	{
		SmartDashboard& dashboard = *SmartDashboard::GetInstance();
		char buffer[20];
		sprintf (buffer, "% 2.1f", value);
		dashboard.PutString (name, buffer);
	}

	Command *m_autonomousCommand;
	
	//! A counter to ensure the smart dashboard is updated frequently but
	//! not continuously
	unsigned m_dashboardCounter;
};

START_ROBOT_CLASS(ReboundRumbleBot);
