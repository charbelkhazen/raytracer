#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

typedef struct s_sphere
{
    t_obj   *obj;
    t_vec   center;
    double  radius;
}   t_sphere;

void sph_create(t_sphere sphere, t_vec center, double radius);

#endif
