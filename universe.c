#include "universe.h"

void	univ_init(t_univ *univ, t_obj *obj_lst, int cap)
{
	univ->obj_lst = obj_lst;
	univ->len = 0;
	univ->cap = cap;
}

int	univ_push(t_univ *univ, t_obj object)
{
	if (univ->len == univ->cap)
		return (0);
	univ->obj_lst[(univ->len)++] = object;
	return (1);
}

void	univ_clear(t_univ *univ)
{
	univ->len=0;
}

