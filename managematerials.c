#include "managematerials.h"
#include "material.h"
#include "stdlib.h"

int	mngmat_new_material(t_mat **material, t_material_list *list)
{
	if (list->count >= MNGMAT_MAX)
		return (1);
	*material = &(list->data)[(list->count)++];
	return (0);
}

void	mngmat_access_material_i(t_mat **material, t_material_list *list, int i)
{
	std_assert(i >= 0 && i < list->count);

	*material = &list->data[i];
}
