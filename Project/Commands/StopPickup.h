#ifndef STOPPICKUP_H
#define STOPPICKUP_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class StopPickup: public CommandBase {
public:
	StopPickup();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
