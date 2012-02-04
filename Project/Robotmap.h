#ifndef ROBOTMAP_H
#define ROBOTMAP_H


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
	k_rearRightJaguar = 4
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
#define k_driveMaxOutputVoltage 6
#define k_useEncoders false

#endif
