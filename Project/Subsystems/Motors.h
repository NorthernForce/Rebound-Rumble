#ifndef MOTORS_H
#define MOTORS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANJaguar.h"

/**
 * @brief This class will be used to instantiate all of the
 * motors that will be used on the robot. Putting all of the 
 * motors here will make programming everything much easier.
 *
 * @author Arthur Lockman
 */
class Motors: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Motors();
	void InitDefaultCommand();
	CANJaguar *frontLeftMotor;
	CANJaguar *frontRightMotor;
	CANJaguar *rearLeftMotor;
	CANJaguar *rearRightMotor;
	//All of the individual motors will go here.
};

#endif
