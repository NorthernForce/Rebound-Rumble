#ifndef RAISERAMPMANIPULATOR_H
#define RAISERAMPMANIPULATOR_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class RaiseRampManipulator: public CommandBase {
private:
	int _state;
public:
	RaiseRampManipulator();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
