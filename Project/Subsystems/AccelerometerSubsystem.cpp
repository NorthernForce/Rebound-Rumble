#include "AccelerometerSubsystem.h"
#include "../Robotmap.h"

/**
 * @brief Constructor for the Accelerometer Subsystem. 
 * Creates the Accelerometer object.
 * 
 * @author Arthur Lockman
 */
AccelerometerSubsystem::AccelerometerSubsystem() :
	Subsystem("AccelerometerSubsystem"),
	m_i2c (0),
	m_spi (0),
	m_x (0.01, 0.005),
	m_y (0.01, 0.005),
	m_z (0.01, 0.005),
	m_currentState (eNotPresent)
{
	InitializeSensor();
}

/**
 * @brief Sets the default command for the subsystem.
 */
void AccelerometerSubsystem::InitDefaultCommand()
{
}

/** @brief Initializes the sensor by connecting to the physical device
 *
 * @author Stephen Nutt
 */
void AccelerometerSubsystem::InitializeSensor()
{
	// Delete any previous physical devices
	delete m_i2c;
	m_i2c = 0;
	delete m_spi;
	m_spi = 0;

	// First try I2C
	m_i2c = new ADXL345_I2C (1);
	if (GetRawVector().Magnitude() == 0.0)
	{
		// No I2C device found - check SPI
		delete m_i2c;
		m_i2c = 0;
//		m_spi = new ADXL345_SPI (1, k_Accl_SPI_CK, k_Accl_SPI_DI, k_Accl_SPI_DO, k_Accl_SPI_CS);
		if (GetRawVector().Magnitude() == 0.0)
		{
			delete m_spi;
			m_spi = 0;
			return;
		}
	}

	// If the sensor was not previously calibrated, begin the process now
	if (m_currentState == eNotPresent)
	{
		m_currentState = eNotCalibrated;
		BeginStationaryCalibrartion();
	}
}

/** @brief Begins the stationary calibration process
 *
 * @author Stephen Nutt
 */
void AccelerometerSubsystem::BeginStationaryCalibrartion()
{
	m_currentState = eInStationaryCalibration;
	m_x.Clear();
	m_y.Clear();
	m_z.Clear();
}

/** @brief Begins the stationary calibration process
 *
 * @author Stephen Nutt
 */
void AccelerometerSubsystem::BeginActiveCalibrartion (
	bool forward)
{
	if (m_currentState == eInStationaryCalibration)
	{
		m_zAxis = Vector3D (m_x.GetValue(), m_y.GetValue(), m_z.GetValue());
		m_zAxis.Normalize();
		m_currentState = forward ? eInForwardCalibration : eInReverseCalibration;
	}
	else if (m_currentState == eInForwardCalibration ||
			 m_currentState == eInReverseCalibration)
	{
		// When called a subsequent time, reset the the filters.  This provides
		// a faster method for the dynamic portion of the calibration process
		m_x.Clear();
		m_y.Clear();
		m_z.Clear();
	}
}

/** @brief Executes the basic calibration routines.
 *
 * @author Stephen Nutt
 */
void AccelerometerSubsystem::PerformCalibrartion()
{
	if (m_currentState == eCalibrated)
		return;

	const Vector3D v = GetRawVector();
	if (v.Magnitude())
	{
		const UINT32 now = GetFPGATime();
		m_x.Update (v.x, now);
		m_y.Update (v.y, now);
		m_z.Update (v.z, now);
	}
	else
	{
		InitializeSensor();
	}
}

/** @brief Terminates the calibration routines
 *
 * @author Stephen Nutt
 */
void AccelerometerSubsystem::EndCalibrartion()
{
	if (m_currentState == eInForwardCalibration || m_currentState == eInReverseCalibration)
	{
		const Vector3D currentVal (m_x.GetValue(), m_y.GetValue(), m_z.GetValue());
		if (m_currentState == eInForwardCalibration)
			m_yAxis = currentVal - m_zAxis;
		else
			m_yAxis = m_zAxis - currentVal;

		m_yAxis.Normalize();
		m_xAxis = m_yAxis.CrossProduct (m_zAxis);
		m_xAxis.Normalize();

		m_x.SetCorrectionGains (0.1, 0.05);
		m_y.SetCorrectionGains (0.1, 0.05);
		m_z.SetCorrectionGains (0.1, 0.05);
		m_currentState = eCalibrated;
	}
}

/** @brief Returns the calibrated vector of the accelerometer
 *
 * @author Stephen Nutt
 */
Vector3D AccelerometerSubsystem::GetAccelerations() const
{
	const Vector3D current (GetRawVector());
	return Vector3D (m_xAxis.DotProduct (current), m_yAxis.DotProduct (current), m_zAxis.DotProduct (current));
}

/** @brief Obtains the raw uncalibrated acceleration vector from the
 * physical accelerometer device
 *
 * @author Stephen Nutt
 */
Vector3D AccelerometerSubsystem::GetRawVector() const
{
	if (m_i2c)
	{
		const ADXL345_I2C::AllAxes axes = m_i2c->GetAccelerations();
		return Vector3D (axes.XAxis, axes.YAxis, axes.ZAxis);
	}
	else if (m_spi)
	{
		const ADXL345_SPI::AllAxes axes = m_spi->GetAccelerations();
		return Vector3D (axes.XAxis, axes.YAxis, axes.ZAxis);
	}
	else
	{
		return Vector3D (0, 0, 0);
	}
}
