#include "Turret.h"
#include "../Robotmap.h"
#include "../Commands/ManualShoot.h"
#include "../Commands/CalibrateTurret.h"


TurretMotors::TurretMotors()  try:
	m_turretJaguar((printf("Initializing turret jaguar. \n"), k_turretJaguar))
{
	m_turretJaguar.ChangeControlMode(CANJaguar::kPosition);
	m_turretJaguar.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	m_turretJaguar.SetPID(k_turretP,k_turretI,k_turretD);
	m_turretJaguar.SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
	m_turretJaguar.ConfigEncoderCodesPerRev(k_encoderPulsesPerRev);
	m_turretJaguar.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);
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
//	SetDefaultCommand(new CalibrateTurret());
}

/**
 * @brief Sets the current set position of the Turret jag.
 * @param Angle The position to set it to in radians.
 */
void Turret::SetPosition(float Angle)
{
	float posAngle = Angle/k_turretRad;
	m_turretJaguar.Set(-posAngle);
}
/**
 * @brief Gets the current set position of the Turret jag.
 * @return The current position of the turret in radians.
 */
double Turret::GetPosition()
{
	return -m_turretJaguar.GetPosition()*(k_turretRad);
}

/**
 * @brief Enables control at a certain position.
 * @param position The position to enable control at, in radians.
 */
void Turret::EnableControl(double position)
{
	m_turretJaguar.EnableControl(position/(k_turretRad));
}

/**
 * @brief Disables the jaguar.
 */
void Turret::DisableControl()
{
	m_turretJaguar.DisableControl();
}

/**
 * @brief Gets whether or not one of the limits is hit.
 */
bool Turret::GetLimit()
{
	return m_turretJaguar.GetForwardLimitOK();
}

void Turret::SetMaxVoltage(double voltage)
{
	m_turretJaguar.ConfigMaxOutputVoltage(voltage);
}

/**
 * @brief [DEPRECATED] Turns the turret at a specified speed.
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
