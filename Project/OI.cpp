#include "OI.h"
#include "Commands/CaptureImages.h"
#include "Commands/ChangeControlMode.h"
#include "Commands/Fire.h"
#include "Commands/LogAccelerometer.h"
#include "Commands/FollowRobot.h"
#include "Commands/ShootBall.h"
#include "Commands/RaiseRampManipulator.h"
#include "Commands/LowerRampManipulator.h"
#include "Commands/StartPickup.h"
#include "Commands/StopPickup.h"
#include "Commands/TurnTurretLeft.h"
#include "Commands/TurnTurretRight.h"
#include "Robotmap.h"

/** 
 * @brief Constructs all of the Operator
 * Interface classes for interacting with
 * the robot.
 */
OI::OI() try :
	m_imageButton(&m_stick, k_XBoxButtonA),
    m_logAccelerometerButton(&m_stick, k_XBoxButtonX),
	m_followButton(&m_stick, k_XBoxButtonB),
	m_encoderEnableButton(&m_stick, k_XBoxButtonBack),
	m_encoderDisableButton(&m_stick, k_XBoxButtonStart),
	m_loadButton(&m_stick, k_XBoxButtonY),
	m_raiseButton(&m_stick, k_XBoxButtonRight),
	m_lowerButton(&m_stick, k_XBoxButtonLeft),
    m_startPickupButton(&m_manipulatorStick, k_XBoxButtonStart),
    m_stopPickupButton(&m_manipulatorStick, k_XBoxButtonBack),
    m_turnTurretLeft(&m_manipulatorStick, k_XBoxButtonA),
    m_turnTurretRight(&m_manipulatorStick, k_XBoxButtonB),
	
    m_stick(),
    m_manipulatorStick(2)
//	m_driverstationEnhancedIO(DriverStation::GetInstance()->GetEnhancedIO())
{
	// Process operator interface input here.
    m_imageButton.WhenPressed(new CaptureImages());
    m_logAccelerometerButton.WhenPressed(new LogAccelerometer());
    //m_turnTurretLeft.WhileHeld(new TurnTurretLeft());
    //sm_turnTurretRight.WhileHeld(new TurnTurretRight());
    m_encoderEnableButton.WhenPressed(new ChangeControlMode(true));
    m_encoderDisableButton.WhenPressed(new ChangeControlMode(false));
    m_followButton.WhileHeld(new FollowRobot());
    m_loadButton.WhenPressed(new ShootBall());
    m_raiseButton.WhenPressed(new RaiseRampManipulator());
    m_lowerButton.WhenPressed(new LowerRampManipulator());
    m_startPickupButton.WhenPressed(new StartPickup());
    m_stopPickupButton.WhenPressed(new StopPickup());
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
	return m_stick;
}
