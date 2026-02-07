#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "object.h"
#include "ray.h"
#include "interval.h"

#define OBJLST_CAP 100

typedef struct s_hitRec t_hitRec;

typedef struct s_univ
{
	t_obj	obj_lst[OBJLST_CAP];
	int	count;
}	t_univ;

//mandatory initialization - sets count to 0
void	univ_init(t_univ *univ);

//adds obj to univ at last index - returns 1 on err (exceeded capacity)
int	univ_addObj(t_univ *univ, t_obj obj);

//point to last added obj
void	univ_pointLastObj(t_obj **obj, t_univ *univ);

//FUNCTION HERE HAS TWO ROLES
//returns 1 if hit 0 otherwise. Fills Record if hit
int	univ_hit(t_ray *ray, t_univ *univ, t_hitRec *rec, t_interval *time_interval);
//does it make sense to have rec as input here -> review where exactly is rec used. see render

#endif
