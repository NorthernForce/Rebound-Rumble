#include "Turret.h"
#include "../Robotmap.h"
#include "../Commands/ManualShoot.h"




TurretMotors::TurretMotors()  try:
	m_turretJaguar((printf("Initializing turret jaguar. \n"), k_turretJaguar))
	{
		m_turretJaguar.ChangeControlMode(CANJaguar::kPercentVbus);
		m_turretJaguar.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
		m_turretJaguar.EnableControl();	
		printf("Turret jaguar successfully created. \n");
	}
	catch (exception e)
	{
		printf("Error creating turret jaguars.");
		printf(e.what());
	}
Turret::Turret(): Subsystem("Turret"),
		m_leftLimit(k_turretLeftLimit),
		m_rightLimit(k_turretRightLimit)
{
	
}

void Turret::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ManualShoot());
}
void Turret::SetAngle(float Angle)
{
	
}
void Turret::TurnTurret(float Angle)
{
	
}

float Turret::GetAngle()
{
	return 0.0; // TODO: Implement this.
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
	m_turretJaguar.Set(speed);
}

/**
 * @brief Gets whether or not one of the limits on the 
 * turret is hit.
 * 
 * @return A bool, whether the limit is hit or not.
 */
bool Turret::AtLimit()
{
	if (m_leftLimit.Get())
		return true;
	else if (m_rightLimit.Get())
		return true;
	else
		return false;
}
