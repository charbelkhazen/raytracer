#include "sphere.h"
#include "ray.h"
#include "stdlib.h"
#include <math.h>

typedef struct s_sph_quadParams
{
	double	a;
	double	h;
	double	c;
	double	delta;
}	t_sph_quadParams;

static void	sph_solveQuadratic(t_sph_quadParams *params, t_sph *sphere, t_ray *ray)
{
	t_vec	oc;

	vec_subs(&oc, &sphere->center, &ray->orig);
	params->a = vec_squaredLen(&ray->dir);
	params->h = vec_dot(&ray->dir, &oc);
	params->c = vec_squaredLen(&oc) - sphere->radius * sphere->radius;
	params->delta = (params->h * params->h - params->a * params->c);
}

int	sph_hit(t_sph *sphere, t_ray *ray, double t_min, double t_max, t_hitRec *rec)
{
	t_sph_quadParams	params;
	t_vec	normal_non_unit;
	double	sqrtd;
	double	root;

	sph_solveQuadratic(&params, sphere, ray);
	if (params.delta < 0)
		return (0);
	sqrtd = sqrt(params.delta);
	root = (params.h - sqrtd) / params.a;
	if (root <= t_min || root >= t_max)
	{
		root = (params.h + sqrtd) / params.a;
		if (root <= t_min || root >= t_max)
			return (0);
	}
	rec->t = root;
	ray_at(&rec->p, ray, root);
	vec_subs(&normal_non_unit, &rec->p, &sphere->center);
	vec_scale(&rec->normal, 1.0 / sphere->radius, &normal_non_unit);
	return (1);
}
