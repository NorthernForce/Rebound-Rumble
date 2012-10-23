#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) 
{
}

// Initialize a single static instance of all subsystems to NULL
Drive* CommandBase::s_drive = NULL;
BallShooter* CommandBase::s_ballShooter = NULL;
BallPickup* CommandBase::s_ballPickup = NULL;
BallLifter* CommandBase::s_ballLifter = NULL;
Camera* CommandBase::s_camera = NULL;
GyroSubsystem* CommandBase::s_gyro = NULL;
MaxbotixUltrasonic* CommandBase::s_ultrasonicSensor = NULL;
MaxbotixUltrasonic* CommandBase::s_targetingUltrasonicSensor = NULL;
AccelerometerSubsystem* CommandBase::s_accelerometer = NULL;
Turret* CommandBase::s_turret = NULL;
RampManipulator* CommandBase::s_RampManipulator = NULL; 

OI* CommandBase::oi = NULL;

void CommandBase::init() 
{
    // Create a single static instance of all of your subsystems.
	s_drive = new Drive();
	s_ballShooter = new BallShooter();
	s_ballLifter = new BallLifter();
	s_camera = new Camera();
    s_ballPickup = new BallPickup();
	s_gyro = new GyroSubsystem();
	//s_ultrasonicSensor = new MaxbotixUltrasonic (k_MaxbotixUltrasonic, k_MaxbotixSerialMode, k_MaxbotixOn);
	//s_targetingUltrasonicSensor = new MaxbotixUltrasonic (k_targetingUltrasonic, k_targetingUltrasonicSerialMode, k_targetingUltrasonicOn);
	s_accelerometer = new AccelerometerSubsystem();
	s_turret = new Turret();
	s_RampManipulator = new RampManipulator(); 
	
	oi = new OI();
}
