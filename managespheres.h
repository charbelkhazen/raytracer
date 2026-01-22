//TODO: MANAGE FOR COUNT > CAPACITY
#ifndef MANAGESPHERES_H
#define MANAGESPHERES_H

#define MNGSPH_MAX 100

#include "sphere.h"

typedef struct s_sphere_list
{
	//data represent the list of spheres (called "data" for naming coherence)
	t_sph	data[MNGSPH_MAX];
	int		count;
}	t_sphere_list;

//point to last available sphere in list and count ++.return (1) on err (more than available spheres)
int	mngsph_new_sphere(t_sph **sphere, t_sphere_list *list);

//point to sphere i in list
void	mngsph_access_sphere_i(t_sph **sphere, t_sphere_list *list, int i);


#endif
