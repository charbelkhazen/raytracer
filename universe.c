#include "universe.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"
#include <stdlib.h> //for exit(139) line 52

#include "shape.h"

void	univ_init(t_univ *univ)
{
	univ->count = 0;
}

int	univ_addObj(t_univ *univ, t_obj obj)
{
	if (univ->count >= OBJLST_CAP)
		return (1);
	univ->obj_lst[(univ->count)++] = obj;
	return (0);
}

void	univ_pointLastObj(t_obj **obj, t_univ *univ)
{
	std_assert(univ->count > 0);

	*obj = &(univ->obj_lst[(univ->count) - 1]);
}

static void	univ_obj_apply_material(t_obj obj, t_hitRec *rec)
{
	if (obj.mat.type == MATTE_TYPE)
		rec->material = obj.mat;
	else
		exit(139);
}

static int	univ_obj_hit_sphere(t_obj obj, t_ray ray, t_hitRec *rec, double tmin, double *tmax)
{
	if (!sph_hit(obj.shape.as.sphere, ray, tmin, *tmax, rec))
		return (0);
	*tmax = rec->t;
	univ_obj_apply_material(obj, rec);
	return (1);
}

static int	univ_obj_try_hit(t_obj obj, t_ray ray, t_hitRec *rec, double tmin, double *tmax)
{
	if (obj.shape.type == SPHERE_TYPE)
		return (univ_obj_hit_sphere(obj, ray, rec, tmin, tmax));
	return (0);
}

static int	univ_iterate_hits(t_ray ray, t_univ univ, t_hitRec *rec, double tmin, double *tmax)
{
	int	i;
	int	hit;

	i = 0;
	hit = 0;
	while (i < univ.count)
	{
		if (univ_obj_try_hit(univ.obj_lst[i], ray, rec, tmin, tmax))
			hit = 1;
		i++;
	}
	return (hit);
}

int	univ_hit(t_ray ray, t_univ univ, t_hitRec *rec)
{
	double	tmin;
	double	tmax;

	tmin = 0.001;
	tmax = 1e6;
	return (univ_iterate_hits(ray, univ, rec, tmin, &tmax));
}
