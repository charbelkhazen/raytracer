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
	t_obj object;
	t_mat material;
	t_sph sphere;

	char str[100];

	printf("%d\n",pars_parseCamera(&obj, &sphere, &material, "0.0,0.0,20.6 12.6 10,0,255"));
	printf("shape type:%c\n", obj.obj_shapeType);
	t_sphere sub;
	sub = (t_sph *)obj.obj_shape;
	vec_toStr(str, &sub.center, 1);
	printf("center:%s\nradius:%f", str, sub.radius);
}
