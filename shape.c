#include "shape.h"
#include "vector.h"
#include "sphere.h"

void	shape_fillSphere(t_shape *shape, t_vec center, double radius)
{
	shape->type = SPHERE_TYPE;
	sph_fillSph(&shape->as.sphere, center, radius);
}
