#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#define M_PI 3.1415926535897932384626433832795
#include <math.h>


/**
 * @brief The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 *
 * @author Arthur Lockman
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// #define LEFTMOTOR 1
// #define RIGHTMOTOR 2

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

//CAN Jaguars
enum JaguarsAddress
{
	k_frontLeftJaguar = 2,
	k_frontRightJaguar = 4,
	k_rearLeftJaguar = 3,
	k_rearRightJaguar = 5,
	k_turretJaguar = 9,
	k_flywheelFrontJaguar = 6,
	k_flywheelBackJaguar = 7,
};

enum AnalogAddress
{
	k_MaxbotixUltrasonic = 1,
	k_targetingUltrasonic = 2,
};

enum DigitalAddress
{
	k_Accl_SPI_CK = 1,
	k_Accl_SPI_DI = 2,
	k_Accl_SPI_DO = 3,
	k_Accl_SPI_CS = 4,
	k_MaxbotixSerialMode = 5,
	k_MaxbotixOn = 6,
	k_liftLimit = 7,
	k_turretLeftLimit = 8,
	k_turretRightLimit = 9,
	k_targetingUltrasonicSerialMode = 10,
	k_targetingUltrasonicOn = 11,
};

enum EnhancedIODigitalAddresses
{
	//! Digital inputs/outputs on the PSoC
	k_fireButton = 1,
	k_rejectbutton = 2,
	k_manualSwitch = 3,
	k_openChuteButton = 4,
	k_closeChuteButton = 5,
	k_feederSwitch = 6,
	k_noTargetLED = 7,
	k_hasTargetLED = 8,
	k_autoLED = 9,
	k_manualLED = 10,
	k_lowerRampButton = 11,
	k_dIO12 = 12,
};
enum EnhancedIOAnalogAddresses
{
	//!Analog inputs on the PSoC modules.
	k_turretAngle = 1,
	k_velocitySlider = 2,
	k_aI3 = 3,
	k_aI4 = 4,
	k_aI5 = 5,
};

// PWM Assigments
enum PWMAddress
{
//	k_pwmCameraPan  = 1,
//	k_pwmCameraTilt = 2,
	k_LeftServoPort = 3,
	k_RightServoPort = 4,
};

enum RelayPort
{
    k_liftMotorRelay = 6,
    k_pickupMotorRelay = 2,
    k_rampManipulatorRelayRight = 4,
    k_rampManipulatorRelayLeft = 5,
};

#define k_rampValue 0.4
#define k_followDistanceInches 24
#define k_followDeadband 2

//Xbox Controller Ports
#define k_XBoxButtonA 1
#define	k_XBoxButtonB 2
#define	k_XBoxButtonX 3
#define	k_XBoxButtonY 4
#define	k_XBoxButtonLeft 5
#define	k_XBoxButtonRight 6
#define	k_XBoxButtonBack 7
#define	k_XBoxButtonStart 8
#define	k_XBoxButtonLeftJoystick 9
#define	k_XBoxButtonRightJoystick 10
#define k_driveJoystickPort 1
#define k_manipulatorJoystickPort 2

//Acceleration of Gravity (meters per second)
#define k_GravityAccel 9.8
#define k_ArrivalAngle 45.0

// Number of Images to capture when the image capture button
// is held down
#define k_ImageCaptureCount 10

static const float k_secTheta = 1/cos(M_PI/3);
static const float k_tanTheta = tan(M_PI/3);
static const float k_sinTheta = sin(M_PI/3);
static const float k_cosTheta = cos(M_PI/3);
static const float k_spinupTolerance = 1;
static const float k_shooterHeight = 1.1; // TODO:measure this
static const float k_targetHeight = (98)*0.0254 - k_shooterHeight; // in meters
static const float k_visionTargetHeight = 1.5 * (0.0254  *12);//in meters
static const float k_visionTargetWidth = 2 * (0.0254 * 12);//in meters
static const float k_aAngleMin = M_PI/6; // in radians
static const float k_aAngleMax = M_PI/3; // in radians
static const float k_maxMatchTime = 135; // in seconds
static const float k_cameraViewAngle = 43.5; // in degrees
static const float k_vMax = 10; // TODO: set this to a reasonable value
static const float k_vMin = 0;
static const float k_maxDistance = k_vMax * k_cosTheta * (sqrt(k_sinTheta*k_sinTheta * k_vMax*k_vMax - 2 * k_GravityAccel * k_targetHeight) + k_vMax * k_sinTheta);
static const float k_spinConstantA = 1.924;
static const float k_spinConstantB = 23.865;
static const float k_shooterWheelRadius = (6)*(0.0254);
static const float k_driveWheelRadius = 12*0.0254;
static const float k_driveGearRatio = 1/12.75;
static const float k_turretCenter = 3.3;

//PID Values
static const float k_driveP = -0.3;
static const float k_driveI = 0.0;
static const float k_driveD = 0.0;
static const float k_shooterP = 17;
static const float k_shooterI = .01;
static const float k_shooterD = 1;
static const float k_turretP = 960.000;
static const float k_turretI = 3.200;
static const float k_turretD = 32767.000;
static const int k_shooterEncoderLines = 65535;
static const float k_shooterMaxOutputVoltage = 12;
static const int k_encoderPulsesPerRev = 256;
static const int k_driveMaxOutputVoltage = 12;
static const bool k_useEncoders = false;

#endif
