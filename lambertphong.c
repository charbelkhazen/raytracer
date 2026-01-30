# include "ray.h"
# include "universe.h"
# include "intersection.h"
# include "light.h"
# include <math.h>
# include "ambientlight.h"
# include "scene.h"
/*
** very naive : assumes all objects are opaque !!
*/
int	lp_attenuationFactor(t_ray *ray_to_light, t_univ *univ)
{
	t_hitRec	rec;

	if (univ_hit(ray_to_light, univ, &rec))
		return (0);
	return (1);
}

void	lp_specular(
	t_vec *color,
	t_ray *ray,
	t_hitRec *rec,
	t_light *light,
	t_ray *rayToLight
)
{
	// Blinn-Phong reflection
	t_vec	halfwayVector;
	double	color_scalar;
	t_vec	white_color;
	double	shininess;

	shininess = 50.0; // TODO: parameterize later

	vec_subs(&halfwayVector, &rayToLight->dir, &ray->dir);
	vec_unitVector(&halfwayVector, &halfwayVector);

	vec_fillVec(&white_color, 1, 1, 1);
	color_scalar = pow(
		fmax(vec_dot(&halfwayVector, &rec->normal), 0.0),
		shininess
	) * light->bright;

	vec_scale(color, color_scalar, &white_color);
}

void	lp_lambert(
	t_vec *color,
	t_hitRec *rec,
	t_light *light,
	t_ray *rayToLight
)
{
	double	color_scalar;

	color_scalar = light->bright * vec_dot(&rec->normal, &rayToLight->dir);

	if (color_scalar < 0)
		color_scalar = 0;

	vec_scale(color, color_scalar, &rec->color);
}

static void	lp_capColorToOne(t_vec *color)
{
	if (color->x > 1) color->x = 1;
	if (color->y > 1) color->y = 1;
	if (color->z > 1) color->z = 1;
}

void	lp_shade(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene)
{
	t_ray	rayToLight;
	int		att_factor;
	t_vec	specular_color;
	t_vec	lambert_color;
	t_vec			ambient_color;

	light_rayToLight(&rayToLight, &rec->p, &scene->light.src);
	att_factor = lp_attenuationFactor(&rayToLight, &scene->univ);

	lp_lambert(&lambert_color, rec, &scene->light, &rayToLight);
	lp_specular(&specular_color, ray, rec, &scene->light, &rayToLight);

	vec_add(color, &specular_color, &lambert_color);
	vec_scale(color, att_factor, color);
	lp_capColorToOne(color);

	// ambient
	// find exact ambient color (color * ratio) and cap Color (> 255 -> 1 and < 0 -> 0)

	vec_scale(&ambient_color, scene->ambient.ratio, &scene->ambient.color);
	vec_add(color, color, &ambient_color);
	lp_capColorToOne(color);
}
