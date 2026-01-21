#ifndef MANAGESPHERES_H
#define MANAGESPHERES_H

#include "sphere.h"

typedef struct s_sphere_list
{
	//data represent the list of spheres (called "data" for naming coherence)
	t_sph	*data;
	int		capacity;
	int		count;
}	t_sphere_list;

//gets an initialized undefined t_sph *list_of_spheres and its capacity 
void	mngsph_sphere_list_init(t_sphere_list *list, t_sph *list_of_spheres, int capacity);

//get last t_sph sphere in sphere and count ++
void	mngsph_new_sphere(t_sph *sphere, t_sphere_list *list);

//t_sph *sphere will point to sphere i is list
void	mngsph_access_sphere_i(t_sph *sphere, t_sphere_list list, int i);


#endif
