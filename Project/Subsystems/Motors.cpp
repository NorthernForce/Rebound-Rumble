#include "Motors.h"
#include "../Robotmap.h"
#include "CANJaguar.h"

/**
 * @brief The constructor for the motors. This method
 * will instantiate all of the motor objects for the 
 * robot.
 * 
 * @author Arthur Lockman
 */

Motors::Motors() : Subsystem("Motors")
{
	try 
	{
		printf("Initializing front left jaguar.");
		frontLeftMotor = new CANJaguar(k_frontLeftJaguar);
		frontLeftMotor->ChangeControlMode(CANJaguar::kPercentVbus);
		frontLeftMotor->ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
		frontLeftMotor->EnableControl();
		
		printf("Initializing front right jaguar.");
		frontRightMotor = new CANJaguar(k_frontRightJaguar);
		frontRightMotor->ChangeControlMode(CANJaguar::kPercentVbus);
		frontRightMotor->ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
		frontRightMotor->EnableControl();
		
		printf("Initializing rear left jaguar."); 
		rearLeftMotor = new CANJaguar(k_rearLeftJaguar);
		rearLeftMotor->ChangeControlMode(CANJaguar::kPercentVbus);
		rearLeftMotor->ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
		rearLeftMotor->EnableControl();
		
		printf("Initializing rear right jaguar.");
		rearRightMotor = new CANJaguar(k_rearRightJaguar);
		rearRightMotor->ChangeControlMode(CANJaguar::kPercentVbus);
		rearRightMotor->ConfigMaxOutputVoltage(k_driveMaxOutputVoltage);
		rearRightMotor->EnableControl();
	} 
	catch (exception e)
	{
		printf("Error creating jaguars.");
		printf(e.what());
	}
}
    
void Motors::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
