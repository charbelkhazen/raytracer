# include "ray.h"
# include "universe.h"
# include "intersection.h"
# include "light.h"

//very naive : assumes all objects are opaque !!
int	lp_attenuationFactor(t_ray ray_to_light, t_univ univ)
{
	t_hitRec	rec;

	if (univ_hit(&ray_to_light, &univ, &rec))
		return (0);
	return (1);
}

void	lp_shade(t_vec *color, t_hitRec rec, t_ray ray, t_light light, t_univ univ)
{
	t_ray	rayToLight;
	int	att_factor;

	light_rayToLight(&rayToLight, &rec.p, &light.src);
	att_factor = lp_attenuationFactor(rayToLight, univ);
	
	t_vec	obj_color;
	t_vec	normal;
	double	light_brightness;
	
	
	obj_color = rec.material.color;
	normal = rec.normal;
	light_brightness = light.bright;

	double color_scalar;

	color_scalar = light_brightness * vec_dot(&normal, &rayToLight.dir);
	//light behind surface or brightness negative
	if (color_scalar < 0)
		color_scalar = 0;
	vec_scale(color, color_scalar, &obj_color);
	vec_scale(color, att_factor, color);
}

