#include "shape.h"
#include "vector.h"
#include "sphere.h"
#include "plane.h"

void	shape_fillSphere(t_shape *shape, t_vec center, double radius)
{
	shape->type = SPHERE_TYPE;
	sph_fillSph(&shape->as.sphere, center, radius);
}

int	shape_hit(t_shape *shape, t_ray *ray, double t_min, double t_max, t_hitRec *rec)
{
	if (shape->type == SPHERE_TYPE)
		return (sph_hit(&shape->as.sphere, ray, t_min, t_max, rec)); 

	if (shape->type == PLANE_TYPE)
		return (plane_hit(ray, &shape->as.plane, t_min, t_max, rec));  //TODO: swap the order of ray and plane parameters to make it consistent with other hit funcions
	
	if (shape->type == CYLINDER_TYPE)
		return (cyl_hit(&shape->as.cylinder,ray,  t_min, t_max, rec)); 

	return (0);
}
