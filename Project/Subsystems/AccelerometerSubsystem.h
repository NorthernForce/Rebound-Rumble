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

	//! Call to begin the stationary calibration process
	void BeginStationaryCalibrartion();

	//! Call to begin the stationary calibration process
	void BeginActiveCalibrartion (bool forward);

	//! Call frequently to calibrate the accelerometer
	void PerformCalibrartion();

	//! Call to end calibration
	void EndCalibrartion();

	//! Returns the current acceleration vector
	Vector3D GetAccelerations() const;

private:
	enum State
	{
		eNotCalibrated,
		eInStationaryCalibration,
		eInForwardCalibration,
		eInReverseCalibration,
		eCalibrated
	};

	//! The physical accelerometer
	ADXL345_I2C m_accelerometer;

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
