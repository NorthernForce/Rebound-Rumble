#ifndef RAMPMANIPULATOR_H
#define RAMPMANIPULATOR_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Mike E
 */
class RampManipulator: public Subsystem {
private:
public:
	RampManipulator();
	
	void MotorForward();
	void MotorBackward();
	void MotorStop();
	void EngageLock();
	void ReleaseLock();
	void InitDefaultCommand();
	void SetServo(float position);
private:
	Relay m_RampManipulatorMotor; // The window motor
	Servo m_LeftLockServo; 
	Servo m_RightLockServo; 
	float m_LockAngle;
	float m_UnlockAngle;
};

#endif
