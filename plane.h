#ifndef PLANE_H
# define PLANE_H

#include "intersection.h"
#include "vector.h"
#include "ray.h"
#include "interval.h"

typedef struct s_plane
{
	t_vec	point;
	t_vec	normalized_normal;
	t_vec	color;
}	t_plane;

void	plane_fillPlane(t_plane *plane, t_vec point, t_vec normalized_normal, t_vec color);

//returns bool AND if hit fills hitRec
int	plane_hit(t_ray *ray, t_plane *plane, t_interval *time_interval, t_hitRec *rec);
#endif
