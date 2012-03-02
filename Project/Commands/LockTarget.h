#ifndef LOCKTARGET_H
#define LOCKTARGET_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joe
 */
class LockTarget: public CommandBase {
private:

public:
	LockTarget();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
