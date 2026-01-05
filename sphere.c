#include "stdlib.h"

#include <math.h>
#include <stdlib.h>
#include "sphere.h"
#include "ray.h"
#include "object.h"

void sph_create(t_sph *sphere, t_vec center, double radius)
{
	assert(radius >= 0);
	sphere->center = center;
	sphere->radius = radius;
}

static double	sph_getDelta(t_sph *sphere, t_ray *ray)
{
	t_vec	oc;
	double	a;
	double	h;
	double	c;

	oc = v_sub(sphere->center, ray->orig);
	a = v_len2(ray->dir);
	h = v_dot(ray->dir, oc);
	c = v_len2(oc) - sphere->radius * sphere->radius;
	return (h * h - a * c);
}

int sph_hit(t_sph sphere, const t_ray *ray, double t_min, double t_max, t_hitRec *rec)
{
	if (sph_getDelta(sphere, ray) < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a;
	if (root <= t_min || root >= t_max)
	{
		root = (h + sqrtd) / a;
		if (root <= t_min || root >= t_max)
			return (0);
	}
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = v_div(v_sub(rec->p, sphere->center), sphere->radius);
	return (1);
}
