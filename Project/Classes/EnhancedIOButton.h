#ifndef ENHANCEDIOBUTTON_H
#define ENHANCEDIOBUTTON_H
#include <WPILib.h>
#include <Buttons/Button.h>
#include "../Robotmap.h"

/**
 * @brief A controller for an EnhancedIO button.
 * Inherits from the Button class.
 * 
 * @author Arthur Lockman
 */
class EnhancedIOButton: public Button
{
public:
	EnhancedIOButton(int port, DriverStationEnhancedIO::tDigitalConfig mode);
	bool Get();
private:
	DriverStationEnhancedIO& m_dsIO;
	int m_port;
};
#endif
