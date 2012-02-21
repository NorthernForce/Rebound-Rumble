#ifndef BALLPICKUP_H
#define BALLPICKUP_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Joseph Martin
 */
class BallPickup: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
    Relay m_pickupMotor;
public:
	BallPickup();
    void Start();
    void Stop();
	void InitDefaultCommand();
};

#endif
