#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @brief This class controls the Ultrasonic
 * Range Finding Sensor on the robot. All methods
 * for interacting with that sensor will go here.
 *
 * @author Arthur Lockman
 */
class UltrasonicSensor: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	UltrasonicSensor();
	float GetDistance();
	void InitDefaultCommand();
};

#endif
