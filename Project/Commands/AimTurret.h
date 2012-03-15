#ifndef AIMTURRET_H
#define AIMTURRET_H

#include "../CommandBase.h"

/**
 * Aims the turret without using a PID command.
 *
 * @author Arthur Lockman
 */
class AimTurret: public CommandBase {
public:
	AimTurret();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
