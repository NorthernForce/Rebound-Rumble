#ifndef BALLPICKUPCONTROLLER_H
#define BALLPICKUPCONTROLLER_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class BallController: public CommandBase {
public:
	BallController();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
