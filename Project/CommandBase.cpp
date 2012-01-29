#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) 
{
	
}

CommandBase::CommandBase() : Command() 
{
	
}

// Initialize a single static instance of all subsystems to NULL
//Drive* CommandBase::s_drive = NULL;
BallPickup* CommandBase::s_ballPickup = NULL;
BallShooter* CommandBase::s_ballShooter = NULL;
BallStorage* CommandBase::s_ballStorage = NULL;
Camera* CommandBase::s_camera = NULL;
CameraMount* CommandBase::s_cameraMount = NULL;
GyroSubsystem* CommandBase::s_gyro = NULL;
UltrasonicSensor* CommandBase::s_ultrasonicSensor = NULL;
AccelerometerSubsystem* CommandBase::s_accelerometer = NULL;
Motors* CommandBase::s_motors = NULL;
Targeting* CommandBase::s_targeting = NULL;

OI* CommandBase::oi = NULL;

void CommandBase::init() 
{
    // Create a single static instance of all of your subsystems.
	//s_drive = new Drive();
	s_ballPickup = new BallPickup();
	s_ballShooter = new BallShooter();
	s_ballStorage = new BallStorage();
	s_camera = new Camera();
	s_cameraMount = new CameraMount();
	s_gyro = new GyroSubsystem();
	s_ultrasonicSensor = new UltrasonicSensor();
	s_accelerometer = new AccelerometerSubsystem();
	s_motors = new Motors();
	s_targeting = new Targeting();
	
	oi = new OI();
}
