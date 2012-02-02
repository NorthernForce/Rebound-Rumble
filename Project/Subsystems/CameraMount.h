#ifndef CAMERAMOUNT_H
#define CAMERAMOUNT_H
#include <WPILib.h>

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
public:
	CameraMount();
	void Pan(float angle);
	void Tilt(float angle);
	float GetPanAngle();
	float GetTiltAngle();
	void InitDefaultCommand();
};

#endif
