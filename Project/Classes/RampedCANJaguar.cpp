/*
 * RampedCANJaguar.cpp
 *
 *  Created on: Feb 11, 2012
 *      Author: Joseph Martin
 */

#include "RampedCANJaguar.h"
#include "../Robotmap.h"
#include <math.h>

RampedCANJaguar::RampedCANJaguar(int deviceNumber,
                                 float maxVelocity,
                                 float maxAcceleration,
                                 float tolerance = 0,
                                 float thereTolerance = 0) :
    CANJaguar(deviceNumber),
    m_maxAcceleration(maxAcceleration),
    m_maxVelocity(maxVelocity),
    m_tolerance(tolerance),
    m_thereTolerance(thereTolerance),
    m_prevTime(0.0),
    m_prevPosition(0.0),
    m_prevVelocity(0.0),
    m_prevAccel(0.0)
{
    ; // do nothing, all initialization is done above
}

void RampedCANJaguar::SetTolerance(float tolerance, float thereTolerance)
{
    m_tolerance = tolerance;
    m_thereTolerance = thereTolerance;
}

void RampedCANJaguar::SetMaxVelocity(float maxVelocity)
{
    m_maxVelocity = maxVelocity;
}

void RampedCANJaguar::SetMaxAcceleration(float maxAcceleration)
{
    m_maxAcceleration = maxAcceleration;
}

void RampedCANJaguar::DisableControl()
{
    //m_prevPosition = 0.0; // <-- Not sure why we did this last year
    CANJaguar::DisableControl();
}

void RampedCANJaguar::EnableControl(float encoderInitialPosition)
{
    CANJaguar::EnableControl(encoderInitialPosition);
    m_prevPosition = encoderInitialPosition;
}

void RampedCANJaguar::EnableControl()
{
    CANJaguar::EnableControl(m_prevPosition);
}

void RampedCANJaguar::Set(float outputValue, UINT8 syncGroup = 0)
{
    float curTime = GetTime();
    float deltaT = curTime - m_prevTime;
    float position = m_prevPosition;
    float velocity = m_prevVelocity;
    float accel = m_prevAccel;
    switch(GetControlMode()) 
    {

        case kSpeed:
            accel = Limit( (outputValue - m_prevVelocity)/deltaT, m_maxAcceleration );
            velocity = Limit( m_prevVelocity + (accel * deltaT), m_maxVelocity );
            CANJaguar::Set(velocity, syncGroup);
            break;
        case kPosition:
            float deltaP = outputValue - m_prevPosition;
            if ( fabs(deltaP) < m_thereTolerance )
            {
                CANJaguar::Set(outputValue, syncGroup);
                break;
            }
            else if ( fabs(deltaP) < m_tolerance )
            {
                CANJaguar::Set(m_prevPosition + 0.4*(deltaP), syncGroup);
                break;
            }
            velocity = Limit( deltaP/deltaT, m_maxVelocity );
            accel = Limit( (velocity - m_prevVelocity) / deltaT, m_maxAcceleration );
            velocity = m_prevVelocity + accel * deltaT;
            position = m_prevPosition + m_prevVelocity * deltaT + 0.5 * accel * deltaT * deltaT;
            if ( 
                    (((outputValue - position) > 0) && 
                     ((outputValue - position) < ((velocity*velocity) / (2*m_maxAcceleration)))) || 
                    (((outputValue - position) < 0) && 
                     ((outputValue - position) > -((velocity*velocity) / (2*m_maxAcceleration)))) 
               )
            {
                if( (deltaP) > m_tolerance )
                {
                    accel = -m_maxAcceleration;
                } else if ( (deltaP) < -m_tolerance )
                {
                    accel = m_maxAcceleration;
                } 
                velocity = m_prevVelocity + accel * deltaT;
                position = m_prevPosition + m_prevVelocity * deltaT + 0.5 * accel * deltaT * deltaT;
            }
            CANJaguar::Set(position, syncGroup);
            break;
        default:
            CANJaguar::Set(outputValue, syncGroup);
            break;
    }
    m_prevTime = curTime;
    m_prevVelocity = velocity;
    m_prevAccel = accel;
}

float RampedCANJaguar::Limit(float input, float max) 
{
    if (input > max)
    {
        return max;
    } else if (input < -max)
    {
        return -max;
    }
    return input;
}

float RampedCANJaguar::Get()
{
    return m_prevPosition;
}