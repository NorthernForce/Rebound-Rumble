#ifndef DRIVE_H
#define DRIVE_H
#include <WPILib.h>
#include "../Classes/BSBotDrive.h"
#include "../Classes/FRCXboxJoystick.h"

/**
 * @brief The drive object for the robot. All
 * methods for interacting with drive will go
 * here.
 *
 * @author Arthur Lockman
 */
class Drive: public Subsystem{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	BSBotDrive* drive;
public:
	Drive();
	void InitDefaultCommand();
	void DriveWithStick(FRCXboxJoystick& stick);
	void DriveRobot (float speed, float direction);
	void ChangeControlMode (bool enable);
    double GetAvgSpeed() const;

	//! Returns true if the motor safety reports the robot motors are being
	//! corrected fed and are alive
    bool IsAlive() const
    { return drive->IsAlive(); }

	//! Stops all the motors
    void StopMotors() const
    { drive->Stop(); }
};

#endif
