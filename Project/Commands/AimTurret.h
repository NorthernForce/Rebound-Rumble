#ifndef AIMTURRET_H
#define AIMTURRET_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class AimTurret: public CommandBase {
private:
    float angle;
public:
	AimTurret();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
