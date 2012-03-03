#ifndef STOPFIRING_H
#define STOPFIRING_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joe
 */
class StopFiring: public CommandBase {
public:
	StopFiring();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
