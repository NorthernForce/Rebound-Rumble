#ifndef CALIBRATETURRET_H
#define CALIBRATETURRET_H

#include "../CommandBase.h"

/**
 * Calibrates the turret.
 *
 * @author Arthur Lockman
 */
class CalibrateTurret: public CommandBase {
public:
	CalibrateTurret();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
