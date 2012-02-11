#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H
#include <WPILib.h>
#include "../Classes/AlphaBetaFilter.h"
#include "../Classes/Vector3D.h"

/**
 * @brief This class controls the Accelerometer.
 * It contains all methods for interacting with
 * and getting data from that sensor.
 *
 * @author Arthur Lockman
 */
class AccelerometerSubsystem :
	public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	AccelerometerSubsystem();
	void InitDefaultCommand();

	// Initializes the sensor by connecting to the physical device
	void InitializeSensor();
	
	//! Call to begin the stationary calibration process
	void BeginStationaryCalibrartion();

	//! Call to begin the dynamic calibration process while the robot
	//! is moving straight either forwards or backwards
	void BeginActiveCalibrartion (bool forward);

	//! Call frequently to calibrate the accelerometer
	void PerformCalibrartion();

	//! Call to end calibration
	void EndCalibrartion();

	//! Returns true if an accelerometer is present
	inline bool IsPresent() const
	{
		return m_currentState != eNotPresent;
	}

	//! Return true if the accelerometer has been calibrated
	inline bool IsCalibrated() const
	{
		return m_currentState == eCalibrated;
	}

	//! Returns the current acceleration vector
	Vector3D GetAccelerations() const;

private:
	Vector3D GetRawVector() const;

	enum State
	{
		eNotPresent,				//!< No sensor is present
		eNotCalibrated,
		eInStationaryCalibration,
		eInForwardCalibration,
		eInReverseCalibration,
		eCalibrated
	};

	//! The physical accelerometer connected via I2C
	ADXL345_I2C* m_i2c;

	//! The physical accelerometer connected via SPI	
	ADXL345_SPI* m_spi;

	//! Alpha-beta filters are used to reduce the noise from the sensor
	//! providing a more accurate calibration.
	AlphaBetaFilter<double> m_x;
	AlphaBetaFilter<double> m_y;
	AlphaBetaFilter<double> m_z;
	
	Vector3D m_xAxis;	//!< Unit vector right
	Vector3D m_yAxis;	//!< Unit vector forwards
	Vector3D m_zAxis;	//!< Unit vector down

	//! The current calibration state
	State m_currentState;
};

#endif
