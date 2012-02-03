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
    Vector3D(float, float, float);
    float GetMagnitude();
    float x;
    float y;
    float z;
};
#endif
