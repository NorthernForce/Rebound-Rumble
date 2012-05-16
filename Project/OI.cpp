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
    m_driveStick(k_driveJoystickPort),
    m_manipulatorStick(k_manipulatorJoystickPort)
{
	// Stick one buttons
//    m_driveStick.Y.WhenPressed(new ShootBall()); IN USE, CENTERS TURRET
	m_driveStick.A.WhenPressed(new ShootBall());
	m_driveStick.LeftBumper.WhenPressed(new RaiseRampManipulator());
	m_driveStick.RightBumper.WhenPressed(new LowerRampManipulator());

    
    // Stick 2 buttons
	m_manipulatorStick.A.WhenPressed(new ShootBall());
//    m_manipulatorStick.B.WhenPressed(new LockTarget()); IN USE, SCANS TURRET RIGHT
//    m_manipulatorStick.X.WhenPressed(new TurnTurretLeft()); IN USE, SCANS TURRET LEFT
//    m_manipulatorStick.Y.WhenPressed(new ShootBall()); IN USE, CENTERS TURRET
	m_manipulatorStick.LeftBumper.WhenPressed(CreateStopPickup());
	m_manipulatorStick.RightBumper.WhenPressed(CreateStartPickup());
	m_manipulatorStick.Back.WhenPressed(new StopFiring());
    
    printf("All OI elements created successfully.");
    printf("\n");
}
catch (exception e)
{
	printf("Operator Interface failed to initialize.");
}

/**
 * @brief Returns the drive joystick.
 * 
 * @return The drive joystick.
 */
FRCXboxJoystick& OI::GetStick()
{
	return m_driveStick;
}
FRCXboxJoystick& OI::GetManipulatorStick()
{
	return m_manipulatorStick;
}
