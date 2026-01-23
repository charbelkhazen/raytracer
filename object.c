#include "object.h"
#include "vector.h"
#include "sphere.h"
//#include "matte.h"

//need to add material after
void	obj_fillObj(t_obj *obj, t_shape shape, t_vec color)
{
	obj->shape = shape;
	obj->color = color;
}

/*
#include <stdio.h>
int main()
{
	t_obj obj;

	t_sph sphere1;
	t_vec	center1;

	vec_fillVec(&center1, 0, 0, -5);
	sph_fillSph(&sphere1, center1, 1);

	t_vec color;

	vec_fillVec(&color, 1, 1, 0);

	obj_fillObj(&obj, sphere1, color);
}
*/
