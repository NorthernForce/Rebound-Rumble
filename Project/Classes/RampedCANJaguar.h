#ifndef RAMPEDCANJAGUAR_H
#define RAMPEDCANJAGUAR_H

#include <WPILib.h>
#include <CANJaguar.h>
/*
 * RampedCANJaguar.h
 *
 *  Created on: Feb 11, 2012
 *      Author: Joseph Martin
 */

/*
 * Description:
 */
class RampedCANJaguar : public CANJaguar 
{
private:
    float m_maxAcceleration;
    float m_maxVelocity;
    float m_tolerance;
    float m_thereTolerance;
    float m_prevTime;
    float m_prevPosition;
    float m_prevVelocity;
    float m_prevAccel;
    float Limit(float in, float max);
public:
    RampedCANJaguar(int deviceNumber, float maxVelocity, float maxAcceleration, float m_tolerance, float m_thereTolerance);
    void SetMaxAcceleration(float maxAcceleration);
    void SetMaxVelocity(float maxVelocity);
    void SetTolerance(float tolerance, float thereTolerance);
    void DisableControl();
    void EnableControl(float encoderInitialPosition);
    void EnableControl();
    void Set(float outputValue, UINT8 syncGroup);
    float Get();
};
#endif
