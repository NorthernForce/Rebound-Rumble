#include "CommandBase.h"
#include "Subsystems/Drive.h"
#include "Subsystems/BallPickup.h"
#include "Subsystems/BallShooter.h"
#include "Subsystems/BallStorage.h"
#include "Subsystems/Camera.h"
#include "Subsystems/CameraMount.h"
#include "Subsystems/GyroSubsystem.h"
#include "Subsystems/UltrasonicSensor.h"
#include "Subsystems/Accelerometer.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) 
{
	
}

CommandBase::CommandBase() : Command() 
{
	
}

// Initialize a single static instance of all subsystems to NULL
Drive* CommandBase::drive = NULL;
BallPickup* CommandBase::s_ballPickup = NULL;
BallShooter* CommandBase::s_ballShooter = NULL;
BallStorage* CommandBase::s_ballStorage = NULL;
Camera* CommandBase::s_camera = NULL;
CameraMount* CommandBase::s_cameraMount = NULL;
GyroSubsystem* CommandBase::s_gyro = NULL;
UltrasonicSensor* CommandBase::s_ultrasonicSensor = NULL;
Accelerometer* CommandBase::s_accelerometer = NULL;

OI* CommandBase::oi = NULL;

void CommandBase::init() 
{
    // Create a single static instance of all of your subsystems.
	s_drive = new Drive();
	s_ballPickup = new BallPickup();
	s_ballShooter = new Ballshooter();
	s_ballStorage = new BallStorage();
	s_camera = new Camera();
	s_cameraMount = new CameraMount();
	s_gyro = new GyroSubsystem();
	s_ultrasonicSensor = new UltrasonicSensor();
	s_accelerometer = new Accelerometer();
	
	oi = new OI();
}
