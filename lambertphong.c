# include "ray.h"
# include "universe.h"
# include "intersection.h"
# include "light.h"
# include <math.h>

//very naive : assumes all objects are opaque !!
int	lp_attenuationFactor(t_ray ray_to_light, t_univ univ)
{
	t_hitRec	rec;

	if (univ_hit(&ray_to_light, &univ, &rec))
		return (0);
	return (1);
}

void	lp_specular(t_vec *color, t_ray ray, t_hitRec rec, t_light light, t_univ univ)
{
	//Blinn-Phong reflection
	t_vec	halfwayVector;
	double	color_scalar;
	t_vec	white_color;
	double	shininess;

	shininess = 1.0; // MUST BE PASSED AS PARAMETER ULTIMATELY

	vec_subs(&halfwayVector, &light.src, &ray.dir);
	vec_unitVector(&halfwayVector, &halfwayVector);

	vec_fillVec(&white_color, 1, 1, 1);
	color_scalar = pow(vec_dot(&halfwayVector, &rec.normal), shininess) * light.bright;
	vec_scale(color, color_scalar, &white_color); 
}

//add to it ambient effect
void	lp_shade(t_vec *color, t_hitRec rec, t_light light, t_univ univ)
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
