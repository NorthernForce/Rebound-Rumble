#include <WPILib.h>
#include "../Robotmap.h"
#include "../Classes/EnhancedIOButton.h"
#include "Buttons/Button.h"
#include "Buttons/PressedButtonScheduler.h"

/**
 * @brief Constructs the Enhanced IO button.
 * 
 * @param port The button port.
 * @param mode The mode to run the button in.
 */
EnhancedIOButton::EnhancedIOButton(int port, DriverStationEnhancedIO::tDigitalConfig mode):
	m_dsIO(DriverStation::GetInstance()->GetEnhancedIO())
{
	m_port = port;
	m_dsIO.SetDigitalConfig(m_port, mode);
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
