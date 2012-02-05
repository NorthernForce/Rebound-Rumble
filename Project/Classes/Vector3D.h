#ifndef VECTOR3D_H
#define VECTOR3D_H
/*
 * Vector3D.h
 *
 *  Created on: Jan 24, 2012
 *      Author: Joseph Martin
 */

/*
 * Description:
 */
class Vector3D {
public:
    Vector3D();
    Vector3D(float x_init, float y_init, float z_init);
    float GetMagnitude();
    float x;
    float y;
    float z;
};
#endif
