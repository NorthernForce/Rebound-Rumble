#ifndef TURRET_H
#define TURRET_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Joe
 */
class Turret: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	float m_currentAngle; //radians
public:
	Turret();
	void SetAngle(float Angle);
	void TurnTurret(float Angle);
	void InitDefaultCommand();
};

#endif
