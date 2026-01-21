#include "managematerials.h"
#include "material.h"
#include "stdlib.h"

void	mngmat_material_list_init(t_material_list *list, t_mat *data, int capacity)
{
	list->data = data;
	list->capacity = capacity;
	list->count = 0;
}

void	mngmat_new_material(t_mat **material, t_material_list *list)
{
	*material = &(list->data)[(list->count)++];
}

void	mngmat_access_material_i(t_mat **material, t_material_list *list, int i)
{
	std_assert(i >= 0);

	*material = &list->data[i];
}
