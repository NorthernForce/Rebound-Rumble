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
	m_i2c (1),
	m_x (0.01, 0.005),
	m_y (0.01, 0.005),
	m_z (0.01, 0.005),
	m_currentState (eNotPresent)
{
	// If we can read a non 0 vector then it is present and the stationary
	// calibration process is started
	if (GetRawVector().Magnitude() != 0.0)
	{
		m_currentState = eInStationaryCalibration;
	}
}

void AccelerometerSubsystem::EnableLogging()
{
	m_x.EnableLogging();
	m_y.EnableLogging();
	m_z.EnableLogging();
}

void AccelerometerSubsystem::DisableLogging()
{
	m_x.DisableLogging();
	m_y.DisableLogging();
	m_z.DisableLogging();
}

void AccelerometerSubsystem::WriteLog(ostream& os)
{
	m_x.WriteLog(os);
	m_y.WriteLog(os);
	m_z.WriteLog(os);
}

void AccelerometerSubsystem::Update(UINT32 currTime)
{
	Vector3D accelerations = this->GetAccelerations();
	m_x.Update(accelerations.x, currTime);
	m_y.Update(accelerations.y, currTime);
	m_z.Update(accelerations.z, currTime);
}

/**
 * @brief Sets the default command for the subsystem.
 */
void AccelerometerSubsystem::InitDefaultCommand()
{
}

/** @brief Begins the stationary calibration process
 *
 * @author Stephen Nutt
 */
void AccelerometerSubsystem::BeginStationaryCalibrartion()
{
    m_x.SetCorrectionGains(0.001, 0);
    m_y.SetCorrectionGains(0.001, 0);
    m_z.SetCorrectionGains(0.001, 0);
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
	const UINT32 now = GetFPGATime();
	m_x.Update (v.x, now);
	m_y.Update (v.y, now);
	m_z.Update (v.z, now);
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
	const ADXL345_I2C::AllAxes axes = m_i2c.GetAccelerations();
	return Vector3D (axes.XAxis, axes.YAxis, axes.ZAxis);
}
