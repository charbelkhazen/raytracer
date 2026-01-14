#include <math.h>

double wrapAngle180(double angle)
{
    angle = fmod(angle, 360.0);
    if (angle < 0)
        angle += 360.0;

    if (angle > 180.0)
        angle = 360.0 - angle;

    return angle;
}
