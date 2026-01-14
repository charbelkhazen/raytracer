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


#include <stdio.h>
int main()
{
	printf("%f\n", wrapAngle180(-360)); 
	printf("%f\n", wrapAngle180(-361)); 
	printf("%f\n", wrapAngle180(360)); 
	printf("%f\n", wrapAngle180(370)); 
}
