#include "managespheres.h"
#include "sphere.h"

void	mngsph_sphere_list_init(t_sphere_list *list, t_sph *buffer, int capacity)
{
	list->data = buffer;
	list->capacity = capacity;
	list->count = 0;
}
