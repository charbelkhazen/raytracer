#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "material.h"
#include "shape.h"

typedef struct s_hitRec t_hitRec;

typedef struct s_obj
{
	t_shape		shape;
	t_mat		mat;
	t_vec		color;
}	t_obj;

void	obj_fillObj(t_obj *obj, t_shape shape, t_mat mat, t_vec color);

int	obj_hit(t_obj *obj, t_ray *ray, double t_min, double t_max, t_hitRec *rec);

#endif



/*
t_shape shape;
t_mat   mat;
t_obj   obj;

shape_fillSphere(&shape, center, radius);
mat_fillMatte(&mat, onoff);
obj_fillObj(&obj, shape, mat, color);
*/
