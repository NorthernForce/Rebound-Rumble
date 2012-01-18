#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @brief This class controls the Accelerometer.
 * It contains all methods for interacting with
 * and getting data from that sensor.
 *
 * @author Arthur Lockman
 */
class Accelerometer: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Accelerometer();
	void InitDefaultCommand();
};

#endif
