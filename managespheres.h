#ifndef MANAGESPHERES_H
#define MANAGESPHERES_H

#include "sphere.h"

typedef struct s_sphere_list
{
	t_sph	*data;
	int		capacity;
	int		count;
}	t_sphere_list;

void	mngsph_sphere_list_init(t_sphere_list *list, t_sph *buffer, int capacity);

//void	mngsph_new_sphere(

#endif
