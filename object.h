#include "vector.h"
#include "sphere.h"
#include "matte.h" // uncomment when fixed

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

typedef struct s_obj
{
	t_shape		shape;
	t_material	material;
	t_vec		color;
}	t_obj;

//need to add material after
void	obj_fillObj(t_obj *obj, t_shape shape, t_material mat, t_vec color);
