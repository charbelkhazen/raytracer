#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "object.h"

typedef struct s_universe
{
	t_obj	*obj_lst; //if requires alloc, refactor to univ[100]
	int	len;
	int	cap;
}	t_univ;

void	univ_init(t_univ *univ, t_obj *empty_lst_objects, int lst_capacity);

int	univ_add(t_univ *univ, t_obj object);

void	univ_clear(t_univ *univ);


#endif
