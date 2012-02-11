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

/** @brief Called continously as the command runs
 *
 * @author Stephen Nutt
 */
void CalibrateAccelerometer::Execute()
{
	switch (m_executeCount++)
	{
	case 0:
		s_accelerometer->BeginActiveCalibrartion (true);
		s_drive->DriveRobot (0.1, 0.0);
		break;

	case 1:
		s_accelerometer->BeginActiveCalibrartion (true);
		break;
	}
}

/** @brief Returns true when the command should finish
 *
 * @author Stephen Nutt
 */
bool CalibrateAccelerometer::IsFinished()
{
	return m_executeCount >= 5;
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
