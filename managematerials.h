#ifndef MANAGEMATERIALS_H
#define MANAGEMATERIALS_H

#include "material.h"

typedef struct s_material_list
{
	//data represent the list of materials (called "data" for naming coherence)
	t_mat	*data;
	int		capacity;
	int		count;
}	t_material_list;

//gets an initialized undefined t_mat *list_of_materials and its capacity 
void	mngmat_material_list_init(t_material_list *list, t_mat *list_of_materials, int capacity);

//point to last available material in list and count ++
void	mngmat_new_material(t_mat **material, t_material_list *list);

//point to material i in list
void	mngmat_access_material_i(t_mat **material, t_material_list *list, int i);


#endif
