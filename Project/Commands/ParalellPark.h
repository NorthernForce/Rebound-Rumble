#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "../CommandBase.h"

/**
 *@brief Paralell Parks the robot
 *
 * @author Shreyas
 */
class ParalellPark: public CommandBase {
private:
	double time;
	int done;
public:
	ParalellPark();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
