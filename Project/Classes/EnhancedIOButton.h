#ifndef ENHANCEDIOBUTTON_H
#define ENHANCEDIOBUTTON_H

#include "Buttons/Button.h"
#include "DriverStationEnhancedIO.h"

/**
 * @brief A controller for an EnhancedIO button.
 * Inherits from the Button class.
 * 
 * @author Arthur Lockman
 */
class EnhancedIOButton: public Button {
public:
	EnhancedIOButton(const int port);
	virtual ~EnhancedIOButton() {}
	virtual bool Get();
private:
	DriverStationEnhancedIO& m_dsIO;
	int m_port;
};
#endif
