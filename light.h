#ifndef LIGHT_H
# define LIGHT_H
# include "vector.h"
# include "ray.h"

typedef struct s_light
{
	t_vec	src;
	t_vec	color;
	double	bright;
}	t_light;

//normalized
void	light_rayToLight(t_ray	*ray, t_vec *point, t_vec *light_src);

#endif
