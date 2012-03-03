#ifndef DRIVETORAMP_H
#define DRIVETORAMP_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class DriveToRamp: public CommandBase {
private:
    int count;
    bool finished;
public:
	DriveToRamp();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
    float Limit(float input, float max);
};

#endif
