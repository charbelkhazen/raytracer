#include "cylinder.h"
#include <math.h>

void	cyl_fillCyl(t_cylinder *cyl, t_vec center, t_vec normalized_axis, t_vec color, double diameter, double height)
{
	cyl->center = center;
	cyl->normalized_axis = normalized_axis;
	cyl->color = color;
	cyl->diameter = diameter;
	cyl->radius = diameter / 2.0;
	cyl->height = height;
}

static	void	cyl_normalPointOut(t_vec *normal, t_ray *ray)
{
	if (vec_dot(normal, &ray->dir) > 0)
		vec_scale(normal, -1, normal);
}

static void	cyl_fillRecord(t_cylinder *cyl, t_hitRec *rec, double t, t_ray *ray)
{
	rec->t = t;

	ray_at(&rec->p, ray, t);

	t_vec	center_to_intersection;
	t_vec	point_of_projection;
	t_vec	tmp;
	double	projection_scale;

	vec_subs(&center_to_intersection, &rec->p, &cyl->center);
	projection_scale = vec_dot(&cyl->normalized_axis, &center_to_intersection);
	vec_scale(&tmp, projection_scale, &cyl->normalized_axis);
	vec_add(&point_of_projection, &cyl->center, &tmp);
	vec_subs(&rec->normal, &rec->p, &point_of_projection);
	cyl_normalPointOut(&rec->normal, ray);
	vec_unitVector(&rec->normal, &rec->normal);
	
	//TODO: in sphere, rec stops here : i.e. fills t and p and normal . FORGETS ABOUT SHAPE AND MATERIAL AND COLOR -> DELEGATES IT TO ANOTHRE FUNCTION . DOESNT IT NEED REFACTORING??
}

int	cyl_hit(t_cylinder *cyl, t_ray *ray, double t_min, double t_max, t_hitRec *rec)
{
	double	t; // t  of ray. Remember : ray equation : p + dt
	double	delta;
	double denominator;
	double	u_dot_v;
	t_vec	u;
	t_vec	v;
	t_vec	tmp;

	//find u
	vec_cross(&u, &cyl->normalized_axis, &ray->dir);

	//find denom and check if not zero
	denominator = vec_dot(&u, &u);
	if (fabs(denominator) < 1e-6)
		return (0);

	//find delta and check if >= 0

	//find v before
	vec_subs(&tmp, &cyl->center, &ray->orig);
	vec_cross(&v, &cyl->normalized_axis, &tmp);

	u_dot_v = vec_dot(&u, &v);
	delta = u_dot_v * u_dot_v - vec_dot(&u, &u) * (vec_dot(&v, &v) - cyl -> radius * cyl->radius);
	if (delta < 0)
		return (0);
	
	t = (u_dot_v - sqrt(delta)) / vec_dot(&u, &u);
	
	if (t < t_min || t > t_max)
		return (0);
	
	cyl_fillRecord(cyl, rec, t, ray);
	return (1);
}
