#ifndef LOCKTARGET_H
#define LOCKTARGET_H

#include "../CommandBase.h"

/** @brief Calibrates the accelerometer by moving the robot
 * forwards for s brief moment and detecting the change in
 * the accelerometer
 *
 * @author Stephen Nutt
 */
class CalibrateAccelerometer :
	public CommandBase
{
public:
	CalibrateAccelerometer();
	virtual void Initialize(){}
	virtual void Execute();
	virtual bool IsFinished();
	virtual void Interrupted();
	virtual void End();
	
private:
	//! Counts the number of time Execute is called
	unsigned m_executeCount;
};

#endif
