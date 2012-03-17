#ifndef STARTPICKUP_H
#define STARTPICKUP_H

#include "SimpleCommand.h"
#include "../Subsystems/BallPickup.h"

/**
 *
 *
 * @author Joseph Martin
 */
inline CommandBase* CreateStartPickup()
{
	return new SimpleCommand<BallPickup> ("StartPickup",
		*CommandBase::s_ballPickup, &BallPickup::Start);
}

/**
 *
 *
 * @author Joseph Martin
 */
inline CommandBase* CreateStopPickup()
{
	return new SimpleCommand<BallPickup> ("StopPickup",
		*CommandBase::s_ballPickup, &BallPickup::Stop);
}

#endif
