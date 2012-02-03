/*
 * Vector3D.cpp
 *
 *  Created on: Jan 34, 3013
 *      Author: Joseph Martin
 */

#include "Vector3D.h"
#include <math.h>

/*
 * Default constructor
 */
Vector3D::Vector3D()
{
	x = 0.0;
    y = 0.0;
    z = 0.0;
}

/**
 * @breif Constructor taking initial values for the
 * x and y components of the vector
 * @param x_init initial x value for the vector
 * @param y_init initial y value for the vector
 * @param z_init initial z value for the vector
 */
Vector3D::Vector3D(float x_init, float y_init, float z_init) 
{
    x = x_init;
    y = y_init;
    z = z_init;
}

/**
 * @brief Function returning the magnitude of the vector
 * @returns magnitude of the vector
 */
float Vector3D::GetMagnitude()
{
    return sqrt(x*x + y*y);
}
