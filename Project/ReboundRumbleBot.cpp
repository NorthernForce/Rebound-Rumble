#include <WPILib.h>
#include <Math.h>
#include "CommandBase.h"
#include "Commands/CalibrateAccelerometer.h"

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
		m_pCalibrationCommand = new CalibrateAccelerometer();
	}

	virtual void DisabledInit()
	{
		CommandBase::s_accelerometer->BeginStationaryCalibrartion();
		printf("Disabled.");
	}

	virtual void AutonomousInit() 
	{
		Scheduler::GetInstance()->AddCommand (m_pCalibrationCommand);
		m_autonomousCommand = m_pCalibrationCommand;
	}
	
	virtual void AutonomousPeriodic() 
	{
		CommandBase::s_drive->Feed();
		Scheduler::GetInstance()->Run();
		this->UpdateDashboard();
		//Update the LED on the driver station to say if it has a target or not.
		//@TODO test this.
		if (CommandBase::s_camera)
			CommandBase::oi->SetTargetLEDs(CommandBase::s_camera->HasValidTarget());
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
		Scheduler::GetInstance()->AddCommand (m_pCalibrationCommand);
	}
	
	virtual void TeleopPeriodic() 
	{
		CommandBase::s_drive->Feed();
		Scheduler::GetInstance()->Run();
		this->UpdateDashboard();
		
		//Update the LED on the driver station to say if it has a target or not.
		//@TODO test this.
		if (CommandBase::s_camera)
			CommandBase::oi->SetTargetLEDs(CommandBase::s_camera->HasTarget());
	}

	virtual void DisabledPeriodic()
	{
		this->UpdateDashboard();
		CommandBase::s_accelerometer->PerformCalibrartion();
	}

	/** @brief Updates the values on the dashboard
	 *
	 * @author Stephen Nutt
	 */
	void UpdateDashboard()
	{
		// Only update every 25 cycles (approx every 1/2 second)
		if ((++m_dashboardCounter % 25) != 0) return;

		SmartDashboard& dashboard = *SmartDashboard::GetInstance();
		if (const Camera* const pCamera = CommandBase::s_camera)
		{
			const UINT32 time = pCamera->GetLastFrameProcessingTime();
			SetSmartDashboardDouble ("FPS", time ? 1000000.0 / time : 0.0);
			if (pCamera->HasTarget())
			{
				SetSmartDashboardDouble ("Target Angle", pCamera->GetAngleToTarget());
				SetSmartDashboardDouble("Target Distance",pCamera->GetDistanceToTarget());
			}
			else
			{
				dashboard.PutString ("Target Angle", "No target found.");
				dashboard.PutString("Target Distance","No target found.");
			}

            float arrivalAngle = -atan(k_tanTheta + 2*k_targetHeight/(pCamera->GetHorizontalDistance()));
            if( arrivalAngle < k_aAngleMax &&
                arrivalAngle > k_aAngleMin )
            {
            } else
                dashboard.PutString("Directions", "Target is Ok.");
            {
                if(arrivalAngle > k_aAngleMax) arrivalAngle = k_aAngleMax;
                if(arrivalAngle < k_aAngleMin) arrivalAngle = k_aAngleMin;
                // Distance from target to drive to.
                // Not currently used.
                float x = - 2*k_targetHeight/(k_tanTheta + tan(arrivalAngle));
                SetSmartDashboardDouble("Directions", x - pCamera->GetHorizontalDistance());
            }
		}
		
		if (const MaxbotixUltrasonic* const pUltrasonic = CommandBase::s_ultrasonicSensor)
		{
			SetSmartDashboardDouble ("Target Distance inches", pUltrasonic->GetRangeInInches());
			SetSmartDashboardDouble ("Ultrasonic Analog Voltage",pUltrasonic->GetVoltage());
			SetSmartDashboardDouble ("Target Voltage", pUltrasonic->GetVoltage());
		}
		
		if (const AccelerometerSubsystem* const pAccelerometer = CommandBase::s_accelerometer)
		{
			if (pAccelerometer->IsPresent() == false)
			{
				dashboard.PutString ("Accelerometer X", "Not connected");
				dashboard.PutString ("Accelerometer Y", "Not connected");
				dashboard.PutString ("Accelerometer Z", "Not connected");
				dashboard.PutString ("Level", "Not connected");
			}
			else if (pAccelerometer->IsCalibrated() == false)
			{
				dashboard.PutString ("Accelerometer X", "Uncalibrated");
				dashboard.PutString ("Accelerometer Y", "Uncalibrated");
				dashboard.PutString ("Accelerometer Z", "Uncalibrated");
				dashboard.PutString ("Level", "Uncalibrated");
			}
			else
			{
				Vector3D val = pAccelerometer->GetAccelerations();
				SetSmartDashboardDouble ("Accelerometer X", val.x);
				SetSmartDashboardDouble ("Accelerometer Y", val.y);
				SetSmartDashboardDouble ("Accelerometer Z", val.z);
				val.Normalize();
				SetSmartDashboardDouble ("Level", acos (val.z) * 180 / M_PI);
			}
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
	
	CalibrateAccelerometer* m_pCalibrationCommand;
};

START_ROBOT_CLASS(ReboundRumbleBot);
