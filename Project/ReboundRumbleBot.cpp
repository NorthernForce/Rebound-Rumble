#include <WPILib.h>
#include <Math.h>
#include "CommandBase.h"
#include "Commands/CalibrateAccelerometer.h"
#include "Commands/Autonomous.h"
#include "Commands/SimpleCommand.h"
#include "Commands/AimTurret.h"

/**
 * @brief This class controls the entire robot,
 * everything it does, and all of its interactions
 * with the field, itself, and the operators.
 * 
 * @author Arthur Lockman
 */
class ReboundRumbleBot : public IterativeRobot
{
	enum RobotState
	{
		Disabled,
		AutonomousState,
		Teleop,
	};
public:
	ReboundRumbleBot() :
		m_autonomousCommand (0),
		m_aimCommand (),
		m_dashboardCounter (0),
		m_pCalibrationCommand (0)
	{
	}

protected:
	virtual void RobotInit()
	{
		CommandBase::init();
		//m_pCalibrationCommand = new CalibrateAccelerometer();
        m_autonomousCommand = new Autonomous();
        m_aimCommand = new AimTurret();
	}

	virtual void DisabledInit()
	{
		if (AccelerometerSubsystem* const pAccelerometer = CommandBase::s_accelerometer)
			pAccelerometer->BeginStationaryCalibrartion();
		printf("Disabled.");
	}

	virtual void AutonomousInit()
	{
        Scheduler::GetInstance()->AddCommand(m_autonomousCommand);
	}

	virtual void AutonomousPeriodic() 
	{
		Scheduler::GetInstance()->Run();
		this->UpdateDashboard (AutonomousState);
		//Update the LED on the driver station to say if it has a target or not.
		//@TODO test this.
		if (CommandBase::s_camera)
			CommandBase::oi->SetTargetLEDs(CommandBase::s_camera->HasValidTarget());

		if (AccelerometerSubsystem* const pAccelerometer = CommandBase::s_accelerometer)
			pAccelerometer->Update (GetFPGATime());
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
		Scheduler::GetInstance()->AddCommand (m_aimCommand);
	}
	
	virtual void TeleopPeriodic() 
	{
		Scheduler::GetInstance()->Run();
		this->UpdateDashboard (Teleop);

		if (AccelerometerSubsystem* const pAccelerometer = CommandBase::s_accelerometer)
		{
			pAccelerometer->Update (GetFPGATime());
		}
	}

	virtual void DisabledPeriodic()
	{
		if (CommandBase::s_drive)
		{
			CommandBase::s_drive->StopMotors();
		}

		this->UpdateDashboard (Disabled);
		if (AccelerometerSubsystem* const pAccelerometer = CommandBase::s_accelerometer)
		{
			pAccelerometer->PerformCalibrartion();
		}
	}

	/** @brief Updates the values on the dashboard
	 *
	 * @author Stephen Nutt
	 */
	void UpdateDashboard (RobotState state)
	{
		// Only update every 25 cycles (approx every 1/2 second)
		if ((++m_dashboardCounter % 25) != 0) return;

		SmartDashboard& dashboard = *SmartDashboard::GetInstance();
		if (BallLifter* const pLifter = CommandBase::s_ballLifter)
		{
			dashboard.PutBoolean("Lifter limit switch", pLifter->GetLimit());
		}

		if (const Drive* const pDrive = CommandBase::s_drive)
		{
			double speed = pDrive->GetAvgSpeed();
			SetSmartDashboardDouble("Average Drive Wheel Speed", speed);

			const char* msg;
			if (pDrive->IsAlive())
			{
				msg = "Alive at %d";
			}
			else
			{
				switch (state)
				{
				case Disabled:
				default:
					msg = "Disabled at %d";
					break;

				case AutonomousState:
					msg = "Autonomous stationary at %d";
					break;

				case Teleop:
					printf ("Dead at %d\n", m_dashboardCounter / 25);
					msg = "Dead at %d";
					break;
				}
			}

			char buffer[100];
			sprintf (buffer, msg, m_dashboardCounter / 25);
			dashboard.PutString ("Drive Status", buffer);
		}

		if (const Camera* const pCamera = CommandBase::s_camera)
		{
			const UINT32 time = pCamera->GetLastFrameProcessingTime();
			SetSmartDashboardDouble ("FPS", time ? 1000000.0 / time : 0.0);
			if (pCamera->HasTarget())
			{
				SetSmartDashboardDouble ("Target Angle In Radians", pCamera->GetAngleToTarget());
				SetSmartDashboardDouble ("Target Angle In Degrees", pCamera->GetDegreeAngleToTarget());
				SetSmartDashboardDouble ("Target Distance",pCamera->GetDistanceToTarget());
			}
			else
			{
				dashboard.PutString ("Target Angle In Radians", "No target found.");
				dashboard.PutString ("Target Angle In Degrees", "No target found.");
				dashboard.PutString("Target Distance","No target found.");
			}
			
			SetSmartDashboardDouble ("Turret Setpoint",pCamera->GetTurretSetpoint());
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
			SetSmartDashboardDouble("Shooter Voltage",CommandBase::oi->GetManipulatorStick().GetRawAxis(Joystick::kDefaultYAxis)*.8+.2);
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
			else
			{
				if (pAccelerometer->IsCalibrated() == false)
				{
					dashboard.PutString ("Accelerometer X", "Uncalibrated");
					dashboard.PutString ("Accelerometer Y", "Uncalibrated");
					dashboard.PutString ("Accelerometer Z", "Uncalibrated");
				}
				else
				{
					Vector3D val = pAccelerometer->GetAccelerations();
					SetSmartDashboardDouble ("Accelerometer X", val.x);
					SetSmartDashboardDouble ("Accelerometer Y", val.y);
					SetSmartDashboardDouble ("Accelerometer Z", val.z);
				}

				SetSmartDashboardDouble ("Level", pAccelerometer->GetLevel() * 180 / M_PI);
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

	Autonomous *m_autonomousCommand;
	AimTurret *m_aimCommand;
	
	//! A counter to ensure the smart dashboard is updated frequently but
	//! not continuously
	unsigned m_dashboardCounter;
	
	CalibrateAccelerometer* m_pCalibrationCommand;
};

START_ROBOT_CLASS(ReboundRumbleBot);
