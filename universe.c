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

//refactor
int	univ_hit(t_ray *ray, t_univ *univ, t_hitRec *rec)
{
	t_obj	*obj_lst;
	t_obj	obj;
	int	nobj;
	int	i;
	double	tmax;
	double	tmin;
	int	hit;

	nobj = univ->len;
	obj_lst = univ->obj_lst;
	hit = 0;

	i = 0;
	tmin = 0.001; //  WILL MODIFY LATER
	tmax = 999999; //  WILL MODIFY LATER

	while (i < nobj)
	{
		obj = obj_lst[i];	
		if (obj.obj_shapeType == 's')
		{
			t_sph *sphere;
			sphere = (t_sph *) obj.obj_shape;
			if(sph_hit(sphere, ray, tmin, tmax, rec))
			{
				hit = 1;
				tmax = rec->t;
			}
		}
		else //needs modif, should include cylinder and surface (same as above but with cyl_hit and sur_hit)
			exit(139); // should never happen, find better way of crashing
		i++;
	}
	return (hit);
}
