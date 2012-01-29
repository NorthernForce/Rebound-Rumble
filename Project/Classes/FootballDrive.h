#ifndef FOOTBALLDRIVE_H
#define FOOTBALLDRIVE_H
#include "WPILib.h"
#include "../CommandBase.h"

/**
 *
 *
 */
class FootballDrive :
	public RobotDrive
	{
public:
	FootballDrive (float sensitivity = 0.5);

	//! Drives the robot using a HID controller
	void ArcadeDrive (GenericHID& controller);

	//! Drives the robot using move and rotate values
	void ArcadeDrive (float moveValue, float rotateValue, bool squaredInputs);

	//! Alternate drive to move the robot using move and rotate values
	void ArcadeDrive2 (float moveValue, float rotateValue, bool squaredInputs);

	//! Turns on and off the use of the encoders
	void EnableEncoders (bool enable);

	//! Stops the robot
	void Stop();

private:
	void PowerMotors (float frontLeft, float frontRight);

	void PowerMotors (float frontLeft, float rearLeft, float frontRight, float rearRight);

	bool m_useEncoders;
	
	float m_eSum;
	}
;
#endif
