#include "universe.h"
#include "sphere.c"
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

//refactor
int	univ_throwRay(t_ray *ray, t_univ *univ, t_hitRec *rec)
{
	t_obj	*obj_lst;
	t_obj	obj;
	int	nobj;
	int	i;
	int	tmax;
	int	tmin;
	int	hit;

	nobj = univ->len;
	obj_lst = univ->obj_lst;
	hit = 0;

	i = 0;
	tmin = -999999;// math!
	tmax = 999999; // math!

	while (i < nobj)
	{
		obj = obj_lst[i];	
		if (obj.obj_type == 's')
		{
			hit = sph_hit((t_sph *)&obj, ray, tmin, tmax, rec);
			if (hit)
				if (rec->t < tmax)
					tmax = rec->t;
		}
		else //needs modif, should include cylinder and surface (same as above but with cyl_hit and sur_hit)
			exit(139); // should never happen, find better way of crashing
		i++;
	}
	return (hit);
}
