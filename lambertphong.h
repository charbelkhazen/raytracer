#ifndef LAMBERTPHONG_H
#define LAMBERTPHONG_H
# include "ray.h"
# include "intersection.h"
# include "universe.h"
# include "scene.h"

//all directions should be normalized
void	lp_shade(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene, int recursion_depth);
#endif
