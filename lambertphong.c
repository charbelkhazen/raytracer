# include "ray.h"
# include "universe.h"
# include "intersection.h"
# include "light.h"
# include <math.h>
# include "ambientlight.h"
# include "scene.h"
# include "render.h"
# include "random.h"
# include "interval.h"

static int	lp_attenuationFactor(t_ray *ray_to_light, t_univ *univ, double distance_ray_light)
{
	t_hitRec	rec;
	t_interval	time_interval;

	time_interval.min = 0.001;
	time_interval.max = distance_ray_light;

	if (univ_hit(ray_to_light, univ, &rec, &time_interval))
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

void	lp_lambertPhong(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene, double diffuse_ratio) // diffuse ratio + specular ratio = 1 , and 0<= both ratios <= 1
{
	t_ray	rayToLight;
	int		att_factor;
	t_vec	specular_color;
	t_vec	lambert_color;
	t_vec			ambient_color;

	light_rayToLight(&rayToLight, &rec->p, &scene->light.src);
	double	distance_ray_light; //needs refactoring . see light module to decide how to efficiently refactor
	t_vec	ray_light_vec;
	vec_subs(&ray_light_vec, &rec->p, &scene->light.src);
	distance_ray_light = vec_vectorLen(&ray_light_vec);
	att_factor = lp_attenuationFactor(&rayToLight, &scene->univ, distance_ray_light);

	lp_lambert(&lambert_color, rec, &scene->light, &rayToLight);
	lp_specular(&specular_color, ray, rec, &scene->light, &rayToLight);


	//weightening specular and diffuse effects
	vec_scale(&lambert_color, diffuse_ratio, &lambert_color);
	vec_scale(&specular_color, (1.0 - diffuse_ratio), &specular_color);
	vec_add(color, &specular_color, &lambert_color);

	// Multiply diffuse and specular effect by ATTENUATION FACTOR
	vec_scale(color, att_factor, color);

	// ambient lightninig //TODO: isolate for norminette
	t_vec	tmp;
	vec_scale(&tmp, scene->ambient.ratio, &scene->ambient.color);
	vec_componentWiseMultiplication(&ambient_color,  &tmp, &rec->color);
	vec_add(color, color, &ambient_color);

	//cap to one if > 1 
	lp_capColorToOne(color);
}


void	lp_shade_matte(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene)
{
	lp_lambertPhong(color, rec, ray, scene, 1.0);
}

//0.6 chosen here is heuristics
void	lp_shade_plastic(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene)
{
	lp_lambertPhong(color, rec, ray, scene, 0.6);
}

// r = d - 2(d.n)n
static void	lp_getReflectionRay(t_ray *reflection_ray, t_ray *ray, t_hitRec *rec)
{
	t_vec	tmp;
	t_vec	reflection_dir;

	vec_scale(&tmp, vec_dot(&ray->dir, &rec->normal) * 2.0, &rec->normal);
	vec_subs(&reflection_dir, &ray->dir, &tmp);
	ray_fillRay(reflection_ray, rec->p, reflection_dir);
}

void	lp_shade_mirror(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene, int recursion_depth)
{
	t_ray	reflection_ray;

	//get reflection ray
	lp_getReflectionRay(&reflection_ray, ray, rec);
	//recursive call
	render_rayColor(color, &reflection_ray, scene, recursion_depth - 1); 
}

//sampling ray from unit vector randomly
//in 2d , easy : theta ! U (0, 2pi) then you use x = costheta and y = sintheta (logic circle equation)
//IN 3d you need to incorporate z
//z ~ u(-1,1) and r =sqrt(1 - z^2) seems to come from pythagore geom
//->instead chose v = (rcostheta, rsintheta, z)
static void	lp_sample_unit_vector(t_vec *sampled_unit_vector)
{
	double theta;
	double z;
	double r;

	theta = rand_uniformDistributionSampling(0.0, 2 * M_PI);
	z = rand_uniformDistributionSampling(-1.0, 1.0);
	r = sqrt(1.0 - z * z);
	vec_fillVec(sampled_unit_vector, r * cos(theta), r * sin(theta), z);
}

static void	lp_distortRayWrtRoughness(t_ray *distorted_reflection, t_ray reflection_ray, double metal_roughness)  //If you refactor hitrec, change this then. Rather, access actual roughness from obj
{
	t_vec	sampled_unit_vector;
	t_vec	scaled_by_roughness_unit;

	lp_sample_unit_vector(&sampled_unit_vector);
	if (vec_dot(&sampled_unit_vector, &reflection_ray.dir) < 0)
		vec_scale(&sampled_unit_vector, -1.0, &sampled_unit_vector);
	vec_scale(&scaled_by_roughness_unit, metal_roughness, &sampled_unit_vector);
	vec_add(&distorted_reflection->dir, &scaled_by_roughness_unit, &reflection_ray.dir);
	vec_unitVector(&distorted_reflection->dir, &distorted_reflection->dir);
	distorted_reflection->orig = reflection_ray.orig;
}

void	lp_shade_gold(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene, int recursion_depth)
{
	t_ray	reflection_ray;
	t_vec	albedo;

	//get reflection ray
	lp_getReflectionRay(&reflection_ray, ray, rec);

	lp_distortRayWrtRoughness(&reflection_ray, reflection_ray, 0.01);

	//recursive call
	render_rayColor(color, &reflection_ray, scene, recursion_depth - 1);

	//factor by albedo (metal's "absorption" effect)
	vec_fillVec(&albedo, 1.00, 0.78, 0.34);
	vec_componentWiseMultiplication(color, &albedo, color);
}

void	lp_shade_steel(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene, int recursion_depth)
{
	t_ray	reflection_ray;
	t_vec	albedo;

	//get reflection ray
	lp_getReflectionRay(&reflection_ray, ray, rec);

	lp_distortRayWrtRoughness(&reflection_ray, reflection_ray, 0.01);

	//recursive call
	render_rayColor(color, &reflection_ray, scene, recursion_depth - 1);

	//factor by albedo (metal's "absorption" effect)
	vec_fillVec(&albedo, 0.5, 0.5, 0.5);
	vec_componentWiseMultiplication(color, &albedo, color);
}
void	lp_shade(t_vec *color, t_hitRec *rec, t_ray *ray, t_scene *scene, int recursion_depth)
{
	if (rec->mat == MATTE_TYPE)
		lp_shade_matte(color, rec, ray, scene);
	if (rec->mat == MIRROR_TYPE)
		lp_shade_mirror(color, rec, ray, scene, recursion_depth);
	if (rec->mat == PLASTIC_TYPE)
		lp_shade_plastic(color, rec, ray, scene);
	if (rec->mat == GOLD_TYPE)
		lp_shade_gold(color, rec, ray, scene, recursion_depth);
	if (rec->mat == STEEL_TYPE)
		lp_shade_steel(color, rec, ray, scene, recursion_depth);
}
