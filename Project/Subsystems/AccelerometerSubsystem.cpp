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
	m_accelerometer (1),
	m_x (0.01, 0.005),
	m_y (0.01, 0.005),
	m_z (0.01, 0.005),
	m_currentState (eNotCalibrated)
{
}

/**
 * @brief Sets the default command for the subsystem.
 */
void AccelerometerSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
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
	else if (m_currentState == (forward ? eInForwardCalibration : eInReverseCalibration))
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
	if (m_currentState == eNotCalibrated || m_currentState == eCalibrated)
		return;

	const UINT32 now = GetFPGATime();
	const ADXL345_I2C::AllAxes axes = m_accelerometer.GetAccelerations();
	m_x.Update (axes.XAxis, now);
	m_y.Update (axes.YAxis, now);
	m_z.Update (axes.ZAxis, now);
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
	const ADXL345_I2C::AllAxes axes = m_accelerometer.GetAccelerations();
	const Vector3D current (axes.XAxis, axes.YAxis, axes.ZAxis);
	return Vector3D (m_xAxis.DotProduct (current), m_yAxis.DotProduct (current), m_zAxis.DotProduct (current));
}
