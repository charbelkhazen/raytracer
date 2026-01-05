#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "ray.h"

typedef struct s_sphere
{
	t_obj   *obj;
	t_vec   center;
	double  radius;
}	t_sph;

void	sph_create(t_sph *sphere, t_vec center, double radius);

int	sph_hit(t_sph *sphere, t_ray *ray, double t_min, double t_max, t_hitRec *rec)

#endif
