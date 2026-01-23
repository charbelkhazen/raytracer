#ifndef SHAPE_H
#define SHAPE_H

#include "vector.h"
#include "sphere.h"

typedef enum
{
	SPHERE_TYPE;
	//CYLINDER_TYPE;
	//PLANE_TYPE;
}	shape_type;

typedef struct s_shape
{
	shape_type	type;
	union
	{
		t_sph sphere;
		//t_cyl cylinder;
		//t_pl plane;
	} as;
}	t_shape;


void	shape_fillShape(t_shape *shape, shape_type type);
#endif
