#ifndef AIM_H
#define AIM_H
/*
 * Aim.h
 *
 *  Created on: Jan 24, 2012
 *      Author: Joseph Martin
 */

/*
 * Description:
 */
class Aim {
public:
    // Constructs a new aim object with all values initialized to 0.
    Aim();

    // Constructs a new aim object with initial values.
    // Order is HAngle, VAngle, Velocity
    Aim(float HAngle, float VAngle, float Velocity);

    // Horizontal angle for aiming - this is the angle that the
    // robot must be turned to be aligned with the target.
    float HAngle;

    // Vertical Angle for aiming - angle that the shooter should
    // make with the horizontal.
    float VAngle;

    // Velocity the ball should be shot at. This value should be
    // given to the BallShooter subsystem which will determine what
    // to do to actually shoot the ball at the right velocity.
    float Velocity;
};
#endif
