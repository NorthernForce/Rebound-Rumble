#include "Turret.h"
#include "../Robotmap.h"
#include "../Commands/ManualShoot.h"




TurretMotors::TurretMotors()  try:
	m_turretJaguar((printf("Initializing turret jaguar. \n"), k_turretJaguar))
	{
		m_turretJaguar.ChangeControlMode(CANJaguar::kPosition);
		m_turretJaguar.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
		m_turretJaguar.SetPID(k_turretP,k_turretI,k_turretD);
		m_turretJaguar.SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
		m_turretJaguar.ConfigEncoderCodesPerRev(k_encoderPulsesPerRev);
		m_turretJaguar.ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
		m_turretJaguar.EnableControl();	
		printf("Turret jaguar successfully created. \n");
	}
	catch (exception e)
	{
		printf("Error creating turret jaguars.");
		printf(e.what());
	}
Turret::Turret(): Subsystem("Turret")
{
	
}

void Turret::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ManualShoot());
}
void Turret::SetPosition(float Angle)
{
	m_turretJaguar.Set(Angle);
}

double Turret::GetPosition()
{
	return m_turretJaguar.GetPosition();
}

/**
 * @brief Turns the turret at a specified speed.
 * 
 * @param speed The speed at which to turn the turret.
 */
void Turret::Turn(float speed)
{
	//@TODO uncomment when limits are implemented.
//	if (this->AtLimit())
//	{
//		if (speed < 0 && (m_leftLimit.Get()))
//		{
//			//don't move.
//		} else if (speed > 0 && (m_leftLimit.Get()))
//		{
//			m_turretJaguar.Set(speed);
//		} else if (speed > 0 && (m_rightLimit.Get()))
//		{
//			//don't move.
//		} else if (speed < 0 && (m_rightLimit.Get()))
//		{
//			m_turretJaguar.Set(speed);
//		}
//	}
	//m_turretJaguar.Set(speed);
}
