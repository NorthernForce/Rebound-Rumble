#ifndef SimpleCommand_H
#define SimpleCommand_H

#include "../CommandBase.h"
/**
 * A templated command that executes a single function in a subsystem
 * that takes no arguments
 *
 * Example:
 * new SimpleCommand<AccelerometerSubsystem> ("StopStationaryCalibration",
 *		*CommandBase::s_accelerometer, &AccelerometerSubsystem::EndStationaryCalibrartion);
 *
 *
 * @author Stephen Nutt
 */
template <typename CommandSubsystem>
class SimpleCommand : public CommandBase
{
public:
	// Constructs a new named command for the passed subsystem
	// calling the passed command when executed
	SimpleCommand (const char* const name,
				   CommandSubsystem& subsystem,
				   void (CommandSubsystem::*func)()) :
		CommandBase (name),
		m_subsystem (subsystem),
		m_func (func)
	{
		Requires(&m_subsystem);
	}

	virtual void Initialize() {}

	virtual void Execute()
	{ (m_subsystem.*m_func)(); }

	virtual bool IsFinished()
	{ return true; }

	virtual void End() {}

	virtual void Interrupted() {}

private:
	// The subsystem the command is for
	CommandSubsystem& m_subsystem;

	// The function called in the subsytem
	void (CommandSubsystem::*m_func)();
};

#endif
