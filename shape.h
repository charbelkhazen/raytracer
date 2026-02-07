#ifndef SHAPE_H
#define SHAPE_H

#include "vector.h"
#include "sphere.h"
#include "cylinder.h"
#include "plane.h"
#include "types.h"
#include "interval.h"

typedef struct s_hitRec t_hitRec;

typedef struct s_shape
{
	shape_type	type;
	union
	{
		t_sph sphere;
		t_cylinder cylinder;
		t_plane plane;
	} as;
}	t_shape;

void	shape_fillSphere(t_shape *shape, t_vec center, double radius);
void	shape_fillPlane(t_shape *shape, t_vec point, t_vec normalized_normal, t_vec color);
void	shape_fillCylinder(t_shape *shape, t_vec center, t_vec normalized_axis, t_vec color, double diameter, double height);


int	shape_hit(t_shape *shape, t_ray *ray, t_interval *time_interval, t_hitRec *rec);

#endif
