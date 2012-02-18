#include "CalibrateAccelerometer.h"

/** @brief Creates the command object
 *
 * @author Stephen Nutt
 */
CalibrateAccelerometer::CalibrateAccelerometer() :
	CommandBase ("CalibrateAccelerometer"),
	m_executeCount (0)
{
	Requires (s_accelerometer);
	Requires (s_drive);
}

/** @brief Called to initialize the calibration command
 *
 * @author Stephen Nutt
 */
void CalibrateAccelerometer::Initialize()
{
	m_executeCount = 0;
	s_drive->DriveRobot (1.0, 0.0);
	s_accelerometer->BeginActiveCalibrartion (true);
}

/** @brief Called continuously as the command runs
 *
 * @author Stephen Nutt
 */
void CalibrateAccelerometer::Execute()
{
	if (++m_executeCount == 2)
	{
		s_accelerometer->BeginActiveCalibrartion (true);
	}
	s_accelerometer->PerformCalibrartion();
}

/** @brief Returns true when the command should finish
 *
 * @author Stephen Nutt
 */
bool CalibrateAccelerometer::IsFinished()
{
	return m_executeCount >= 25;
}

void CalibrateAccelerometer::Interrupted()
{
	// As long as we have been executing the calibration routine for at
	// least 1 execution cycle then we likely have reasonable values
	if (m_executeCount > 1)
	{
		s_accelerometer->EndCalibrartion();
	}

	s_drive->DriveRobot (0.0, 0.0);
}

/** @brief Called when the command stops running
 *
 * @author Stephen Nutt
 */
void CalibrateAccelerometer::End()
{
	s_accelerometer->EndCalibrartion();
	s_drive->DriveRobot (0.0, 0.0);
}
