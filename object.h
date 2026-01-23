#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "shape.h"

typedef struct s_obj
{
	t_shape		shape;
	t_mat		mat;
	t_vec		color;
}	t_obj;

void	obj_fillObj(t_obj *obj, t_shape shape, t_mat mat, t_vec color);
#endif
