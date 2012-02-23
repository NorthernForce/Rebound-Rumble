#ifndef AIMTURRET_H
#define AIMTURRET_H

#include "../CommandBase.h"
#include <math.h>
/**
 * This command will aim the turret at the target. While it is
 * running, it will use a PID controller to move the turret
 * based on the error between the turret's current angle with the
 * target and the desired angle with the target (zero). It also
 * has a deadband that will stop the turret if the error is less
 * than a predefined percentage value. This is intended to prevent 
 * "jitter," but it can be easily disabled if this doesn't work.
 * @author Conor McGrory
 */
class AimTurret: public PIDCommand {
public:
	AimTurret();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);
private:
	PIDController* PID_Controller;
	
};

#endif
