#ifndef DRIVEWITHJOYSTICK_H
#define DRIVEWITHJOYSTICK_H

#include "../CommandBase.h"

/**
 * @brief Drives the robot with a joystick. This
 * is the default command for the Drive subsystem.
 *
 * @author Arthur Lockman
 */
class DriveWithJoystick: public CommandBase {
public:
	DriveWithJoystick();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
