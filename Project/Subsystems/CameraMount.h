#ifndef CAMERAMOUNT_H
#define CAMERAMOUNT_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

namespace
{
	const float	mk_panMaxStep  = 1.0;
	const float	mk_panMinStep  = 0.0;
	const float	mk_panMaxRad   = 3.14159265;
	const float	mk_panMinRad   = 0.0;
	const float	mk_tiltMaxStep = 0.5;
	const float	mk_tiltMinStep = 0;
	const float	mk_tiltMaxRad  = 1.5707963;
	const float	mk_tiltMinRad  = 0.0;
	const float mk_stepPerRad  = 0.31830989;
	const float mk_initialPan  = 0.5;
	const float mk_initialTilt = 0.3;
}
/**
 * @brief This class controls the pan
 * and tilt mount for the camera on the
 * robot.
 *
 * @author Arthur Lockman
 */
class CameraMount: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Servo m_panServo;
	Servo m_tiltServo;

	float m_panPos;
	float m_tiltPos;

public:
	CameraMount();
	void Pan(float angle);
	void Tilt(float angle);
	float GetPanAngle();
	float GetTiltAngle();
	void InitDefaultCommand();
};

#endif
