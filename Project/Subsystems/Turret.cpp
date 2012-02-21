#include "Turret.h"
#include "../Robotmap.h"



TurretMotors::TurretMotors()  try:
	m_turretJaguar((printf("Initializing turret jaguar. \n"), k_turretJaguar))
	{
		m_turretJaguar.ChangeControlMode(CANJaguar::kPercentVbus);
		m_turretJaguar.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
		m_turretJaguar.EnableControl();	
		//m_turretJaguar.SetSafetyEnabled(false);
		printf("Turret jaguar successfully created. \n");
	}
	catch (exception e)
	{
		printf("Error creating turret jaguars.");
		printf(e.what());
	}
Turret::Turret() :Subsystem("Turret")
{
	
	
}

void Turret::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
void Turret::SetAngle(float Angle)
{
	
}
void Turret::TurnTurret(float Angle)
{
	
}

float Turret::GetAngle()
{
	return 0.0f; // TODO: Implement this.
}
void Turret::Turn(float speed)
{
	m_turretJaguar.Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
