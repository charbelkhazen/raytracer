#include "managespheres.h"
#include "sphere.h"
#include "stdlib.h"

void	mngsph_sphere_list_init(t_sphere_list *list, t_sph *data, int capacity)
{
	list->data = data;
	list->capacity = capacity;
	list->count = 0;
}

void	mngsph_new_sphere(t_sph **sphere, t_sphere_list *list)
{
	*sphere = &(list->data)[(list->count)++];
}

void	mngsph_access_sphere_i(t_sph **sphere, t_sphere_list *list, int i)
{
	std_assert(i >= 0);

	*sphere = &list->data[i];
}
