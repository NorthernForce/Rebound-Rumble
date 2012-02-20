#ifndef Balance_H
#define Balance_H

#include "../CommandBase.h"
#include "Math.h"
/**
 * This command will balance the robot on the bridge. It assumes 
 * that the accelerations are given in terms of g.
 * @author Conor McGrory
 */
class Balance: public PIDCommand {
public:
	Balance();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);
private:
	float sign(float number);
	float Limit(float input, float max);
	
};

#endif
