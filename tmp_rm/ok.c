#include "parser.h"
#include "light.h"
#include <stdio.h>
#include "vector.h"
#include "ambientlight.h"
# include "viewer.h"
#include "object.h"
#include "sphere.h"
#include "material.h"

int main()
{
	t_obj obj;
	t_mat material;
	t_sph sphere;

	char str[100];

	printf("%d\n",pars_parseSphere(&obj, &sphere, &material, "0.0,0.0,20.6 12.6 10,0,255"));
	printf("shape type:%c\n", obj.obj_shapeType);
	t_sph *sub;
	sub = (t_sph *)obj.obj_shape;
	vec_toStr(str, &sub->center, 1);
	printf("center:%s\nradius:%f\n", str, sub->radius);

	printf("material type:%c\n", obj.obj_matType);

	t_mat *tmp;
	tmp = (t_mat *) obj.obj_mat;
	vec_toStr(str, &tmp->color, 1);
	printf("materia's color:%s\n", str);
}
