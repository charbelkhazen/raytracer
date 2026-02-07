#include "universe.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"
#include <stdlib.h> //for exit(139) line 52
#include "stdlib.h"

#include "shape.h"
#include "interval.h"

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

//fill rec with obj related properties (rec's other fields are filled)
static void	univ_fillRecObj(t_obj *obj, t_hitRec *rec)
{
	rec->color = obj->color;
	rec->shape = obj->shape.type;
	rec->mat = obj->mat.type;
}

static int	univ_obj_hit_and_rec(t_obj *obj, t_ray *ray, t_hitRec *rec, t_interval *time_interval)
{
	if (!obj_hit(obj, ray, time_interval, rec))
		return (0);
	time_interval->max = rec->t;
	univ_fillRecObj(obj, rec);
	return (1);
}

static int	univ_iterate_hits(t_ray *ray, t_univ *univ, t_hitRec *rec, t_interval *time_interval)
{
	int	i;
	int	hit;

	i = 0;
	hit = 0;
	while (i < univ->count)
	{
		if (univ_obj_hit_and_rec(&univ->obj_lst[i], ray, rec, time_interval))
			hit = 1;
		i++;
	}
	return (hit);
}

int	univ_hit(t_ray *ray, t_univ *univ, t_hitRec *rec)
{
	t_interval time_interval;
	double	tmin;
	double	tmax;

	tmin = 0.001;
	tmax = 1e6;

	interval_fillInterval(&time_interval, tmin, tmax);
	return (univ_iterate_hits(ray, univ, rec, &time_interval));
}
