#ifndef SHOOTBALL_H
#define SHOOTBALL_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Arthur Lockman
 */
class ShootBall: public CommandBase {
public:
	ShootBall();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
