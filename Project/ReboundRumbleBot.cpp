#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Classes/FootballDrive.h"

/**
 * @brief This class controls the entire robot,
 * everything it does, and all of its interactions
 * with the field, itself, and the operators.
 * 
 * @author Arthur Lockman
 */
class ReboundRumbleBot : public IterativeRobot 
{
private:
	Command *autonomousCommand;
	FootballDrive *roboDrive;
	
	virtual void RobotInit() 
	{
		CommandBase::init();
		autonomousCommand = new ExampleCommand();
		roboDrive = new FootballDrive();
	}
	
	virtual void AutonomousInit() 
	{
		autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() 
	{
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() 
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		autonomousCommand->Cancel();
	}
	
	virtual void TeleopPeriodic() 
	{
		Scheduler::GetInstance()->Run();
		roboDrive->ArcadeDrive(CommandBase::oi->stick);
	}
};

START_ROBOT_CLASS(ReboundRumbleBot);

