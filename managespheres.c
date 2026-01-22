#include "managespheres.h"
#include "sphere.h"
#include "stdlib.h"

int	mngsph_new_sphere(t_sph **sphere, t_sphere_list *list)
{
	if (list->count >= MNGSPH_MAX)
		return (1);
	*sphere = &(list->data)[(list->count)++];
	return (0);
}

void	mngsph_access_sphere_i(t_sph **sphere, t_sphere_list *list, int i)
{
	std_assert(i >= 0 && i < list->count);

	*sphere = &list->data[i];
}
