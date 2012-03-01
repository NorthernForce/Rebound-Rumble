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
	enum
	{
		StopMotors,
		EngageLock,
		BackOffMotors,
		StopBackOff,
		WaitForStop,
		Complete
	} _state;
public:
	LowerRampManipulator();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
