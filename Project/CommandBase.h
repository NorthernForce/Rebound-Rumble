#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "Subsystems/Drive.h"
#include "Subsystems/BallPickup.h"
#include "Subsystems/BallShooter.h"
#include "Subsystems/BallStorage.h"
#include "Subsystems/Camera.h"
#include "Subsystems/CameraMount.h"
#include "Subsystems/GyroSubsystem.h"
#include "Subsystems/UltrasonicSensor.h"
#include "Subsystems/AccelerometerSubsystem.h"
#include "Subsystems/Motors.h"
#include "Subsystems/Targeting.h"
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
	CommandBase();
	static void init();
	
	// Create instances of subsystems.
	// The "S" prefix denotes a subsystem.
	//static Drive *s_drive;
	static BallPickup *s_ballPickup;
	static BallShooter *s_ballShooter;
	static BallStorage *s_ballStorage;
	static Camera *s_camera;
	static CameraMount *s_cameraMount;
	static GyroSubsystem *s_gyro;
	static UltrasonicSensor *s_ultrasonicSensor;
	static AccelerometerSubsystem *s_accelerometer;
	static Motors *s_motors;
	static Targeting *s_targeting;
	
	//Create operator interface.
	static OI *oi;
};

#endif
