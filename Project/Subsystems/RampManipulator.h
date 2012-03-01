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
	
	void MoveRampDown();
	void MoveRampUp();
	void MotorStop();
	void EngageLock();
	void ReleaseLock();
	void InitDefaultCommand();
	bool m_down;
private:
	Relay m_RampManipulatorMotorRight;
	Relay m_RampManipulatorMotorLeft;// The window motor
	Servo m_LeftLockServo; 
	Servo m_RightLockServo; 
};

#endif
