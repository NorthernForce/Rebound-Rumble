#include "EnhancedIOButton.h"
#include <WPILib.h>

/**
 * @brief Constructs the Enhanced IO button.
 * 
 * @param port The button port.
 */
EnhancedIOButton::EnhancedIOButton(const int port):
	m_dsIO(DriverStation::GetInstance()->GetEnhancedIO())
{
	m_port = port;
	m_dsIO.SetDigitalConfig(m_port, DriverStationEnhancedIO::kInputPullUp);
}

/**
 * @brief Gets the state of the button.
 * 
 * @retun The state of the button, on or off.
 */
bool EnhancedIOButton::Get()
{
	return m_dsIO.GetDigital(m_port);
}
