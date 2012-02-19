#ifndef CHANGECONTROLMODE_H
#define CHANGECONTROLMODE_H

#include "../CommandBase.h"

/**
 * @brief Changes the control mode of the drive jaguars.
 *
 * @author Arthur Lockman
 */
class ChangeControlMode: public CommandBase {
private:
	bool m_usingEncoders;
public:
	ChangeControlMode(bool usingEncoders);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
