#ifndef TURRET_H
#define TURRET_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Joe
 */
class TurretMotors
{
protected:
	TurretMotors();
	CANJaguar m_turretJaguar;
};
class Turret: 
	protected TurretMotors,	
	public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	float m_currentAngle; //radians
public:
	Turret();
	void SetPosition(float Angle);
    double GetPosition();
	void InitDefaultCommand();
	void Turn(float speed);
	void EnableControl(double position = 0.0);
	void DisableControl();
	bool GetLimit();
	void SetMaxVoltage(double voltage);
};

#endif
