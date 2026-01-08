#include "sphere.h"
#include "ray.h"
#include "stdlib.h"
#include <math.h>

typedef struct s_sph_quadParams
{
	double	a;
	double	h;
	double	c;
}	t_sph_quadParams;

static double	sph_getDelta(t_sph *sphere, t_ray *ray, t_sph_quadParams *params)
{
	t_vec	oc;
	double	a;
	double	h;
	double	c;

	oc = vec_subs(&sphere->center, &ray->orig);
	a = vec_squaredLen(&ray->dir);
	h = vec_dot(&ray->dir, &oc);
	c = vec_vectorLen(&oc) - sphere->radius * sphere->radius;
	return (h * h - a * c);
}

int	sph_hit(t_sph *sphere, t_ray *ray, double t_min, double t_max, t_hitRec *rec)
{
	if (sph_getDelta(sphere, ray) < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a; // NEED TO COMP a
	if (root <= t_min || root >= t_max)
	{
		root = (h + sqrtd) / a; //NEED h
		if (root <= t_min || root >= t_max)
			return (0);
	}
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = v_div(v_sub(rec->p, sphere->center), sphere->radius); //wrong usage of functions
	return (1);
}
