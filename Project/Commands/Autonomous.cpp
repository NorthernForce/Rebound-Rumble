#include "Autonomous.h"
#include "ShootBall.h"
#include "SimpleCommand.h"
#include "CalibrateAccelerometer.h"
#include "LowerRampManipulator.h"
#include "Pickup.h"
#include "DriveToRamp.h"
#include "../Subsystems/AccelerometerSubsystem.h"
#include "AimTurret.h"

Autonomous::Autonomous() {
        // Add Commands here:
        // e.g. AddSequential(new Command1());
        //      AddSequential(new Command2());
        // these will run in order.

        // To run multiple commands at the same time,
        // use AddParallel()
        // e.g. AddParallel(new Command1());
        //      AddSequential(new Command2());
        // Command1 and Command2 will run in parallel.

        // A command group will require all of the subsystems that each member
        // would require.
        // e.g. if Command1 requires chassis, and Command2 requires arm,
        // a CommandGroup containing them would require both the chassis and the
        // arm.
	AddParallel(new AimTurret());
	AddSequential(new SimpleCommand<AccelerometerSubsystem>("EndStationaryCalibration",
															*CommandBase::s_accelerometer,
															&AccelerometerSubsystem::EndStationaryCalibration));
	AddSequential(new ShootBall(),6);
	AddSequential(CreateStartPickup());
	AddSequential(new ShootBall(),7);
	AddSequential(new CalibrateAccelerometer());
	//AddParallel(new DriveToRamp());
	//AddSequential(new LowerRampManipulator());
}
