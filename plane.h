#ifndef PLANE_H
# define PLANE_H

#include "intersection.h"
#include "vector.h"
#include "ray.h"

typedef struct s_plane
{
	t_vec	point;
	t_vec	normalized_normal;
	t_vec	color;
}	t_plane;

void	plane_fillPlane(t_plane *plane, t_vec point, t_vec normalized_normal, t_vec color);

//returns bool AND if hit fills hitRec
int	plane_hit(t_ray *ray, t_plane *t_plane, double t_min, double t_max, t_hitRec *rec);
#endif
