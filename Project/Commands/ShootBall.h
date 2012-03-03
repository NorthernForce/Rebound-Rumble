#ifndef SHOOTBALL_H
#define SHOOTBALL_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Arthur Lockman
 */
class ShootBall: public CommandBase {
	int count;
    int m_ballsToShoot;
public:
	ShootBall();
	ShootBall(int num);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
