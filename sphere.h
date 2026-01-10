#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "ray.h"

typedef struct s_sphere
{
	int	type;
	t_vec   center;
	double  radius;
}	t_sph;

void	sph_fillSph(t_sph *sphere, t_vec center, double radius);

int	sph_hit(t_sph *sphere, t_ray *ray, double t_min, double t_max, t_hitRec *rec);

#endif
