#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Subsystems/Drive.h"
#include "Subsystems/BallShooter.h"
#include "Subsystems/BallPickup.h"
#include "Subsystems/Camera.h"
#include "Subsystems/GyroSubsystem.h"
#include "Subsystems/MaxbotixUltrasonic.h"
#include "Subsystems/AccelerometerSubsystem.h"
#include "Subsystems/Drive.h"
#include "Subsystems/Turret.h"
#include "Subsystems/RampManipulator.h"
#include "OI.h"


/**
 * @brief  The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 * 
 * @author Arthur Lockman
 */
class CommandBase: public Command {
public:
	CommandBase(const char *name);

	static void init();
	
	// Create instances of subsystems.
	// The "S" prefix denotes a subsystem.
	static Drive *s_drive;
	static BallShooter *s_ballShooter;
    static BallPickup *s_ballPickup;
	static Camera *s_camera;
	static GyroSubsystem *s_gyro;
	static MaxbotixUltrasonic *s_ultrasonicSensor;
	static AccelerometerSubsystem *s_accelerometer;
	static Turret *s_turret;
	static RampManipulator *s_RampManipulator;
	
	//Create operator interface.
	static OI *oi;
};

#endif
