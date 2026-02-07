//TODO:should remove obj_type from sphere ultimately
#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "intersection.h"
#include "interval.h"

typedef struct s_sphere
{
	int	obj_type;
	t_vec   center;
	double  radius;
}	t_sph;

void	sph_fillSph(t_sph *sphere, t_vec center, double radius);

//returns bool AND if hit fills hitRec
int	sph_hit(t_sph *sphere, t_ray *ray, t_interval *time_interval, t_hitRec *rec);

#endif
