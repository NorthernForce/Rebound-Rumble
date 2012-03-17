#include "OI.h"
#include "Commands/CaptureImages.h"
#include "Commands/ChangeControlMode.h"
#include "Commands/Fire.h"
#include "Commands/LogAccelerometer.h"
#include "Commands/FollowRobot.h"
#include "Commands/ShootBall.h"
#include "Commands/RaiseRampManipulator.h"
#include "Commands/LowerRampManipulator.h"
#include "Commands/Pickup.h"
#include "Commands/TurnTurretLeft.h"
#include "Commands/TurnTurretRight.h"
#include "Commands/ReversePickup.h"
#include "Commands/LockTarget.h"
#include "Commands/StopFiring.h"
#include "Robotmap.h"

/** 
 * @brief Constructs all of the Operator
 * Interface classes for interacting with
 * the robot.
 */
OI::OI() try :
	c_YButton(&m_driveStick, k_XBoxButtonY),
    c_XButton(&m_driveStick, k_XBoxButtonX),
	c_AButton(&m_driveStick, k_XBoxButtonA),
	c_BButton(&m_driveStick, k_XBoxButtonB),
	c_BackButton(&m_driveStick, k_XBoxButtonBack),
	c_StartButton(&m_driveStick, k_XBoxButtonStart),
	c_LeftButton(&m_driveStick, k_XBoxButtonLeft),
	c_RightButton(&m_driveStick, k_XBoxButtonRight),
	
	c2_YButton(&m_manipulatorStick, k_XBoxButtonY),
    c2_XButton(&m_manipulatorStick, k_XBoxButtonX),
	c2_AButton(&m_manipulatorStick, k_XBoxButtonA),
	c2_BButton(&m_manipulatorStick, k_XBoxButtonB),
	c2_BackButton(&m_manipulatorStick, k_XBoxButtonBack),
	c2_StartButton(&m_manipulatorStick, k_XBoxButtonStart),
	c2_LeftButton(&m_manipulatorStick, k_XBoxButtonLeft),
	c2_RightButton(&m_manipulatorStick, k_XBoxButtonRight),
	
    m_driveStick(k_driveJoystickPort),
    m_manipulatorStick(k_manipulatorJoystickPort)
{
	// Stick one buttons
    c_BButton.WhileHeld(new FollowRobot());
    c_YButton.WhileHeld(new ShootBall());
    c_AButton.WhenPressed(new CaptureImages());
    c_XButton.WhenPressed(new LogAccelerometer());
    c_LeftButton.WhenPressed(new RaiseRampManipulator());
    c_RightButton.WhenPressed(new LowerRampManipulator());
    c_StartButton.WhenPressed(new ChangeControlMode(true));
    c_BackButton.WhenPressed(new ChangeControlMode(false)); 
    
    // Stick 2 buttons
    c2_AButton.WhileHeld(new ReversePickup());
    //c2_BButton.WhileHeld(new LockTarget());
    //c2_XButton.WhileHeld(new TurnTurretLeft());
    c2_YButton.WhileHeld(new ShootBall());
    c2_LeftButton.WhenPressed(CreateStopPickup());
    c2_RightButton.WhenPressed(CreateStartPickup());
    c2_StartButton.WhileHeld(new LockTarget());
    c2_BackButton.WhenPressed(new StopFiring());
    
    printf("All OI elements created successfully.");
    printf("\n");
}
catch (exception e)
{
	printf("Operator Interface failed to initialize.");
}
/**
 * @brief Sets the LED's on the operator console.
 * 
 * @param target Whether it has a target or not.
 */
void OI::SetTargetLEDs(bool target)
{
	if (target)
	{
//		m_hasTargetLED.TurnOn();
//		m_noTargetLED.TurnOff();
	} else {
//		m_hasTargetLED.TurnOff();
//		m_noTargetLED.TurnOn();
	}
}

/**
 * @brief Returns the drive joystick.
 * 
 * @return The drive joystick.
 */
XboxJoystick& OI::GetStick()
{
	return m_driveStick;
}
XboxJoystick& OI::GetManipulatorStick()
{
	return m_manipulatorStick;
}
