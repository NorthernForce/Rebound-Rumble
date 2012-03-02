#ifndef REVERSEPICKUP_H
#define REVERSEPICKUP_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class ReversePickup: public CommandBase {
public:
	ReversePickup();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
