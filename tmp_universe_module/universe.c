#include "universe.h"
#include "sphere.h"
#include "intersection.h"
#include <stdlib.h> //for exit(139) line 52

void	univ_init(t_univ *univ, t_obj *obj_lst, int cap)
{
	univ->obj_lst = obj_lst;
	univ->len = 0;
	univ->cap = cap;
}

int	univ_add(t_univ *univ, t_obj *object)
{
	if (univ->len == univ->cap)
		return (0);
	univ->obj_lst[(univ->len)++] = *object;
	return (1);
}

void	univ_clear(t_univ *univ)
{
	univ->len=0;
}

static void	univ_obj_apply_material(t_obj *obj, t_hitRec *rec)
{
	if (obj->obj_matType == 'm')
		rec->material = *(t_mat *)obj->obj_mat;
	else
		exit(139);
}

static int	univ_obj_hit_sphere(t_obj *obj, t_ray *ray, t_hitRec *rec, double tmin, double *tmax)
{
	t_sph	*sphere;

	sphere = (t_sph *)obj->obj_shape;
	if (!sph_hit(sphere, ray, tmin, *tmax, rec))
		return (0);
	*tmax = rec->t;
	univ_obj_apply_material(obj, rec);
	return (1);
}

static int	univ_obj_try_hit(t_obj *obj, t_ray *ray, t_hitRec *rec, double tmin, double *tmax)
{
	if (obj->obj_shapeType == 's')
		return (univ_obj_hit_sphere(obj, ray, rec, tmin, tmax));
	return (0);
}

static int	univ_iterate_hits(t_ray *ray, t_univ *univ, t_hitRec *rec, double tmin, double *tmax)
{
	int	i;
	int	hit;

	i = 0;
	hit = 0;
	while (i < univ->len)
	{
		if (univ_obj_try_hit(&univ->obj_lst[i], ray, rec, tmin, tmax))
			hit = 1;
		i++;
	}
	return (hit);
}

int	univ_hit(t_ray *ray, t_univ *univ, t_hitRec *rec)
{
	double	tmin;
	double	tmax;

	tmin = 0.001;
	tmax = 1e6;
	return (univ_iterate_hits(ray, univ, rec, tmin, &tmax));
}
