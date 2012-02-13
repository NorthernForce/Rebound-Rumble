#include "CameraMount.h"
#include "../Robotmap.h"

/**
 * @brief The constructor for the Camera Mount
 * housing. It has a pan and a tilt servo on
 * it that can be interacted with to set the
 * angle of the viewport on the camera.
 */
CameraMount::CameraMount() :
	Subsystem("CameraMount"),
	m_panServo (k_pwmCameraPan),
	m_tiltServo (k_pwmCameraTilt),
	m_panPos (mk_initialPan),
	m_tiltPos (mk_initialTilt)
{
}

/**
 * @brief Sets the default command for the subsystem.
 */
void CameraMount::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

/**
 * @brief Sets the camera to a certain angle on
 * its horizontal axis.
\ *`o set it to.
 */
void CameraMount::Pan(float angle)
{
	m_panPos = angle * mk_stepPerRad;

	if (m_panPos > mk_panMaxStep)
		m_panPos = mk_panMaxStep;

	if (m_panPos < mk_panMinStep)
		m_panPos = mk_panMinStep;

	m_panServo.SetAngle(m_panPos);
}

/**
 * @brief Sets the camera to a certain angle on
 * its vertical axis.
 *
 * @param angle The angle to set it to.
 */
void CameraMount::Tilt(float angle)
{
	m_tiltPos = angle * mk_stepPerRad;

	if (m_tiltPos > mk_tiltMaxStep)
		m_tiltPos = mk_tiltMaxStep;

	if (m_tiltPos < mk_tiltMinStep)
		m_tiltPos = mk_tiltMinStep;

	m_tiltServo.SetAngle(m_tiltPos);
}

/**
 * @brief Gets the angle that the pan servo
 * is currently set to.
 *
 * @return A float of the angle, relative to 0.
 */
float CameraMount::GetPanAngle()
{
	return (m_panPos / mk_stepPerRad);
}

/**
 * @brief Gets the angle that the tilt servo
 * is currently set to.
 *
 * @return A float of the angle, relative to 0.
 */
float CameraMount::GetTiltAngle()
{
	return (m_tiltPos / mk_stepPerRad);
}
