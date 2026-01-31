#include "plane.h"

void	plane_fillPlane(t_plane *plane, t_vec point, t_vec normalized_normal, t_vec color)
{	
	plane->point = point;
	plane->normalized_normal = normalized_normal;
	plane->color = color;
}

int	plane_hit(t_ray *ray, t_plane *t_plane, double t_min, double t_max, t_hitRec *rec)
{
	double	offset; // This is d in ax + by + cz = d ( plane equation)
	double	denominator; // t = (D - n.P) / n.d. Define the num and denum
	double	numerator;
	double	t; // t  of ray. Remember : ray equation : p + dt

	denominator = vec_dot(plane->normalized_normal, ray->dir);
	if (!denominator)
		return (0);
	offset = vec_dot(plane->normalized_normal, plane->point);
	numerator = offset - vec_dot(plane->normalized_normal, ray->orig);
	t = numerator / denominator;
	if (t < t_min || t > t_max)
		return (0);
	
	return (1);
}
