#include <WPILib.h>
#include "../Robotmap.h"
#include "DriverStationLED.h"

/**
 * @brief Constructs the DriverStation LED.
 * 
 * @param port The LED port.
 */
DriverStationLED::DriverStationLED(int port):
	m_dsIO(DriverStation::GetInstance()->GetEnhancedIO())
{
	m_port = port;
	m_dsIO.SetDigitalConfig(port, DriverStationEnhancedIO::kOutput);
	m_dsIO.SetDigitalOutput(m_port,false);
	m_state = false;
}

/**
 * @brief Gets the state of the LED.
 * 
 * @retun The state of the LED, on or off.
 */
bool DriverStationLED::Get()
{
	return m_state;
}

/**
 * @brief Turns the LED on.
 */
void DriverStationLED::TurnOn()
{
	m_dsIO.SetDigitalOutput(m_port,true);
	m_state = true;
}

/**
 * @brief Turns the LED off.
 */
void DriverStationLED::TurnOff()
{
	m_dsIO.SetDigitalOutput(m_port,false);
	m_state = false;
}

/**
 * @brief Toggles the state of the LED.
 * 
 * @return The state after toggle.
 */
bool DriverStationLED::Toggle()
{
	if (m_state)
	{
		this->TurnOn();
		m_state = true;
	} else {
		this->TurnOff();
		m_state = false;
	}
	return m_state;
}
