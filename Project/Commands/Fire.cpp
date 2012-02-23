#include "Fire.h"
#include "Spinup.h"
#include "AimTurret.h"
#include "ShootBall.h"

/**
 * @brief The constructor for the Fire command.
 */
Fire::Fire() {
        // Add Commands here:
        // e.g. AddSequential(new Command1());
        //      AddSequential(new Command2());
        // these will run in order.
	AddSequential(new AimTurret());
	AddSequential(new Spinup());
	AddSequential(new ShootBall());
        // To run multiple commands at the same time,
        // use AddParallel()
        // e.g. AddParallel(new Command1());
        //      AddSequential(new Command2());
        // Command1 and Command2 will run in parallel.
}
