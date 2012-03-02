#ifndef MANUALSHOOT_H
#define MANUALSHOOT_H

#include "../CommandBase.h"

/**
 * Allows us to manually control the speed of the shooter and the
 * turret motors. Need to change the button that is set to "Fire"
 * to instead call "ShootBall". 
 * 
 * -Conor McGrory
 */
class ManualShoot: public CommandBase {
public:
	ManualShoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
