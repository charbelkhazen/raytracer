#include "plane.h"
#include "interval.h"
#include <math.h>

void	plane_fillPlane(t_plane *plane, t_vec point, t_vec normalized_normal, t_vec color)
{	
	plane->point = point;
	plane->normalized_normal = normalized_normal;
	plane->color = color;
}

static	void	plane_normalPointOut(t_vec *normal, t_ray *ray)
{
	if (vec_dot(normal, &ray->dir) > 0)
		vec_scale(normal, -1, normal);
}

static void	plane_fillRecord(t_plane *plane, t_hitRec *rec, double t, t_ray *ray)
{
	rec->t = t;

	ray_at(&rec->p, ray, t);

	rec->normal = plane->normalized_normal;
	plane_normalPointOut(&rec->normal, ray);

	//TODO: in sphere rec spots here : i.e. fills t and p and normal . FORGETS ABOUT SHAPE AND MATERIAL AND COLOR -> DELEGATES IT TO ANOTHRE FUNCTION . DOESNT IT NEED REFACTORING??
}

int	plane_hit(t_ray *ray, t_plane *plane, t_interval *time_interval, t_hitRec *rec)
{
	double	offset; // This is d in ax + by + cz = d ( plane equation)
	double	denominator; // t = (D - n.P) / n.d. Define the num and denum
	double	numerator;
	double	t; // t  of ray. Remember : ray equation : p + dt

	double t_min = time_interval->min; //TODO: remove both this and instead pass timeinterval
	double t_max = time_interval->max;

	denominator = vec_dot(&plane->normalized_normal, &ray->dir);
	if (!denominator || fabs(denominator) < 1e-6)
		return (0);
	offset = vec_dot(&plane->normalized_normal, &plane->point);
	numerator = offset - vec_dot(&plane->normalized_normal, &ray->orig);
	t = numerator / denominator;
	if (t <= t_min || t >= t_max - 1e-3)
		return (0);
	plane_fillRecord(plane, rec, t, ray);
	return (1);
}
