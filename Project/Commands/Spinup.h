#ifndef SPINUP_H
#define SPINUP_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class Spinup: public CommandBase {
private:
    float velocity;
public:
	Spinup();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
