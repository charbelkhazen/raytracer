#ifndef MANAGEMATERIALS_H
#define MANAGEMATERIALS_H
#define MNGMAT_MAX 100

#include "material.h"

typedef struct s_material_list
{
	//data represent the list of materials (called "data" for naming coherence)
	t_mat	data[MNGMAT_MAX];
	int		count;
}	t_material_list;

//point to last available material in list and count ++. returns (1) on err (above max number of material). 0 otherwise
int	mngmat_new_material(t_mat **material, t_material_list *list);

//point to material i in list
void	mngmat_access_material_i(t_mat **material, t_material_list *list, int i);


#endif
