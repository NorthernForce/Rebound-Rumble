#ifndef LOGACCELEROMETER_H
#define LOGACCELEROMETER_H

#include "../CommandBase.h"
#include <fstream>

/**
 *
 *
 * @author Joseph Martin
 */
class LogAccelerometer: public CommandBase {
private:
    bool finished;
    fstream m_file;
    int m_logNumber;
public:
	LogAccelerometer();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
