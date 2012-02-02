#ifndef CAMERA_H
#define CAMERA_H
#include <WPILib.h>

/**
 * @brief Controls the camera and does the tracking
 * and vision analysis.
 *
 * @author Arthur Lockman
 */
class Camera: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void InitCamera();
public:
	Camera();
	void InitDefaultCommand();
	void Search();
	float GetDistanceToTarget();
	float GetAngleToTarget();
};

#endif
