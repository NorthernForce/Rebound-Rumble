#ifndef STARTPICKUP_H
#define STARTPICKUP_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class StartPickup: public CommandBase {
public:
	StartPickup();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
