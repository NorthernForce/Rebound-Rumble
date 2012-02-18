#ifndef DRIVERSTATIONLED_H
#define DRIVERSTATIONLED_H
#include <WPILib.h>
#include "../Robotmap.h"

/**
 * @brief A controller for an LED on the enhanced IO module.
 * 
 * @author Arthur Lockman
 */
class DriverStationLED
{
public:
	DriverStationLED();
	DriverStationLED(int port);
	bool Get();
	void TurnOn();
	void TurnOff();
	bool Toggle();
private:
	DriverStationEnhancedIO& m_dsIO;
	int m_port;
	bool m_state;
};
#endif
