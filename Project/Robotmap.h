#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#define M_PI 3.1415926535897932384626433832795


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
	k_frontLeftJaguar = 1,
	k_frontRightJaguar = 3,
	k_rearLeftJaguar = 2,
	k_rearRightJaguar = 4,
   	k_pickupMotorJaguar = 5,
   	k_storageMotorJaguar = 6,
	k_flywheelFront = 7,
	k_flywheelBack = 8,
};

enum AnalogAddress
{
	k_MaxbotixUltrasonic = 1,
};
	
enum DigitalAddress
{
	k_Accl_SPI_CK = 1,
	k_Accl_SPI_DI = 2,
	k_Accl_SPI_DO = 3,
	k_Accl_SPI_CS = 4,
	k_MaxbotixSerialMode = 5,
	k_MaxbotixOn = 6,
};

enum EnhancedIOAddresses
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
	k_pwmCameraPan  = 1, 
	k_pwmCameraTilt = 2,
};

enum RelayPort
{
    k_liftMotorRelay = 1,
    k_pickupMotorRelay = 2,
    k_storageMotorRelay = 3,
};

#define k_rampValue 0.4

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
#define k_XBoxJoystickPort 1
#define k_manipulatorJoystickPort 2

//Ball positions.
#define k_ballPosition1 1
#define k_ballPosition2 2
#define k_ballPosition3 3

//Acceleration of Gravity (meters per second)
#define k_GravityAccel 9.8
#define k_ArrivalAngle 45.0

//PID Values and encoder references
#define k_driveP -0.3
#define k_driveI 0.0
#define k_driveD 0.0
#define k_encoderPulsesPerRev 256
#define k_driveMaxOutputVoltage 12
#define k_pickupMaxOutputVoltage 12
#define k_storageMaxOutputVoltage 12
#define k_useEncoders false

// Number of Images to capture when the image capture button
// is held down
#define k_ImageCaptureCount 10

//Enhanced IO module keys
#define k_fireLowerTarget 1
#define k_fireMiddleLeftTarget 2
#define k_fireMiddleRightTarget 3
#define k_fireTopTarget 4

// Pickup motor speed
#define k_pickupMotorSpeed 0
#define k_storageMotorSpeed 0

// Maximum accelerations and velocities
//#define k_maxDriveVelocity 
//#define k_maxDriveAccel 

#endif
