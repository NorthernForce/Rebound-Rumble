#ifndef LOWERRAMPMANIPULATOR_H
#define LOWERRAMPMANIPULATOR_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class LowerRampManipulator: public CommandBase {
private:
	int _state;
public:
	LowerRampManipulator();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
