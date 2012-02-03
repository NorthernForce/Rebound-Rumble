/*
 * Aim.cpp
 *
 *  Created on: Jan 24, 2012
 *      Author: Joseph Martin
 */

#include "Aim.h"
#include <math.h>

/*
 * Default constructor
 */
Aim::Aim()
{
    HAngle = 0.0;
    VAngle = 0.0;
    Velocity = 0.0;
}

/*
 * @breif Constructor taking initial values for the
 * x and y components of the vector
 * @param x_init initial x value for the vector
 * @param y_init initial y value for the vector
 */
Aim::Aim(float HAngle_init, float VAngle_init, float Velocity_init) 
{
    HAngle = HAngle_init;
    VAngle = VAngle_init;
    Velocity = Velocity_init;
}
