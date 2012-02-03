#include "Motors.h"
#include "../Robotmap.h"
#include "CANJaguar.h"

namespace
{
	JaguarsAddress PrintInit (JaguarsAddress addr)
	{
		switch (addr)
		{
		case k_frontLeftJaguar:
			printf("Initializing front left jaguar.");
			break;
		case k_frontRightJaguar:
			printf("Initializing front right jaguar.");
			break;
		case k_rearLeftJaguar:
			printf("Initializing rear left jaguar.");
			break;
		case k_rearRightJaguar:
			printf("Initializing rear right jaguar.");
			break;
		default:
			printf("Unknown Jaguar address.");
			break;
		}

		return addr;
	}
}

/**
 * @brief The constructor for the motors. This method
 * will instantiate all of the motor objects for the 
 * robot.
 * 
 * @author Arthur Lockman
 */

Motors::Motors() try :
	Subsystem("Motors"),
	frontLeftMotor (PrintInit (k_frontLeftJaguar)),
	frontRightMotor (PrintInit (k_frontRightJaguar)),
	rearLeftMotor (PrintInit (k_rearLeftJaguar)),
	rearRightMotor (PrintInit (k_rearRightJaguar))
{
	frontLeftMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	frontLeftMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	frontLeftMotor.EnableControl();
		
	frontRightMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	frontRightMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	frontRightMotor.EnableControl();
		
	rearLeftMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	rearLeftMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	rearLeftMotor.EnableControl();
		
	rearRightMotor.ChangeControlMode(CANJaguar::kPercentVbus);
	rearRightMotor.ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
	rearRightMotor.EnableControl();

	printf("Drive jaguars successfully created.");
} 
catch (exception e)
{
	printf("Error creating jaguars.");
	printf(e.what());
}
    
void Motors::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
