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
	char *buf = "0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225\n";

	pars_parsePlane(&obj, buf);

	/* === OBJECT === */
	print_vec("obj.color", obj.color);

	/* === MATERIAL === */
	printf("mat.type = %d\n", obj.mat.type);
	if (obj.mat.type == MATTE_TYPE)
		printf("mat.matte.onoff = %d\n", obj.mat.as.matte.onoff);

	/* === SHAPE === */
	printf("shape.type = %d\n", obj.shape.type);

	if (obj.shape.type == PLANE_TYPE)
	{
		t_plane *p = &obj.shape.as.plane;

		print_vec("plane.point", p->point);
		print_vec("plane.normal", p->normalized_normal);
		print_vec("plane.color", p->color);
	}

	return 0;
}

