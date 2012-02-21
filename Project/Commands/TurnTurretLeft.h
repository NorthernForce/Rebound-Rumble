#ifndef TURNTURRETLEFT_H
#define TURNTURRETLEFT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joe
 */
class TurnTurretLeft: public CommandBase {
public:
	TurnTurretLeft();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
