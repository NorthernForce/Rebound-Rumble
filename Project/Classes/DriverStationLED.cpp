#include <WPILib.h>
#include "../Robotmap.h"
#include "DriverStationLED.h"
#include "DriverStation.h"

/**
 * @brief Constructs the DriverStation LED.
 * 
 * @param port The LED port.
 */
DriverStationLED::DriverStationLED(int port)
{
	m_port = port;
	DriverStation::GetInstance()->GetEnhancedIO().SetDigitalConfig(port, DriverStationEnhancedIO::kOutput);
	DriverStation::GetInstance()->GetEnhancedIO().SetDigitalOutput(m_port,false);
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
	DriverStation::GetInstance()->GetEnhancedIO().SetDigitalOutput(m_port,false);
	m_state = true;
}

/**
 * @brief Turns the LED off.
 */
void DriverStationLED::TurnOff()
{
	DriverStation::GetInstance()->GetEnhancedIO().SetDigitalOutput(m_port,true);
	m_state = false;
}

/**
 * @brief Toggles the state of the LED.
 * 
 * @return The state after toggle.
 */
bool DriverStationLED::Toggle()
{
	(m_state)?this->TurnOn():this->TurnOff();
	return m_state;
}
