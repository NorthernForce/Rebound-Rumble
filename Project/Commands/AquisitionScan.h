#ifndef AQUISITIONSCAN_H
#define AQUISITIONSCAN_H

#include "../CommandBase.h"
/*
 * AquisitionScan.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jcrosby
 */

/*
 * Description: Scans the Camera Mount until the Image is Found & Centered
 */
class AquisitionScan: public CommandBase {
private:
	int m_rateOfChange;
	float m_angleToTarget;
	float m_initAngle;
	bool m_finished;
public:
	AquisitionScan();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
