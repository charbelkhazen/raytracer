#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "object.h"
#include "ray.h"
#include "vector.h"

typedef struct s_universe
{
	t_obj	*obj_lst; //if requires alloc, refactor to univ[100]
	int	len;
	int	cap;
}	t_univ;

void	univ_init(t_univ *univ, t_obj *empty_lst_objects, int lst_capacity);

int	univ_add(t_univ *univ, t_obj *object);

void	univ_clear(t_univ *univ);

int	univ_throwRay(t_ray *ray, t_univ *univ, t_hitRec *rec);

#endif
