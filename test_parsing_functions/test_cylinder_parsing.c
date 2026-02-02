#include <stdio.h>
#include "object.h"
#include "parser.h"

static void print_vec(const char *name, t_vec v)
{
	printf("%s = (%.6f, %.6f, %.6f)\n", name, v.x, v.y, v.z);
}

int main(void)
{
	t_obj obj;
	char *buf = "50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255\n";

	pars_parseCylinder(&obj, buf);

	/* === OBJECT === */
	print_vec("obj.color", obj.color);

	/* === MATERIAL === */
	printf("mat.type = %d\n", obj.mat.type);
	if (obj.mat.type == MATTE_TYPE)
		printf("mat.matte.onoff = %d\n", obj.mat.as.matte.onoff);

	/* === SHAPE === */
	printf("shape.type = %d\n", obj.shape.type);

	if (obj.shape.type == CYLINDER_TYPE)
	{
		t_cylinder *c = &obj.shape.as.cylinder;

		print_vec("cyl.center", c->center);
		print_vec("cyl.axis", c->normalized_axis);
		print_vec("cyl.color", c->color);

		printf("cyl.diameter = %.6f\n", c->diameter);
		printf("cyl.radius   = %.6f\n", c->radius);
		printf("cyl.height   = %.6f\n", c->height);
	}

	return 0;
}

