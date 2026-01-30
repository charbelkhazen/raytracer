#ifndef LAMBERTPHONG_H
#define LAMBERTPHONG_H
# include "ray.h"
# include "intersection.h"
# include "universe.h"
# include "scene.h"

//naive needs change
int	lp_attenuationFactor(t_ray *ray_to_light, t_univ *univ);

//all directions should be normalized
void	lp_shade(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene);
#endif
