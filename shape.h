#ifndef SHAPE_H
#define SHAPE_H

#include "vector.h"
#include "sphere.h"
#include "cylinder.h"
#include "plane.h"

typedef struct s_hitRec t_hitRec;

typedef enum
{
	SPHERE_TYPE,
	CYLINDER_TYPE,
	PLANE_TYPE,
}	shape_type;

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


int	shape_hit(t_shape *shape, t_ray *ray, double t_min, double t_max, t_hitRec *rec);

#endif
