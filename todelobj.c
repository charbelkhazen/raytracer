//TODO: add t_material
#include "sphere.h"

//#include "matte.h"

typedef struct s_shape
{
	int	type;
	union
	{
		t_sph sphere;
		//t_cyl cylinder;
		//t_pl plane;
	} as;
}	t_shape;

/*
typedef struct s_material
{
	int	type;
	union
	{
		t_mat matte;
		//t_met metallic;
		//t_gl  glass;
	} as;
}	t_material;
*/

typedef struct s_obj
{
	t_shape		shape;
	//t_material	material;
	t_vec		color;
}	t_obj;

//need to add material after
void	obj_fillObj(t_obj *obj, t_shape shape, t_vec color)
{
	obj->shape = shape;
	obj->color = color;
}


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
