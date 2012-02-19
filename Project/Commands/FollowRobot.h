#ifndef FOLLOWROBOT_H
#define FOLLOWROBOT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joe
 */
class FollowRobot: public CommandBase {
private:
public:
	FollowRobot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
