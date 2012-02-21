#ifndef TURNTURRETRIGHT_H
#define TURNTURRETRIGHT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joe
 */
class TurnTurretRight: public CommandBase {
public:
	TurnTurretRight();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
