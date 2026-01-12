#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

typedef struct s_material
{
	char	type; // why  not int
	t_vec	color;
}	t_mat;

void	mat_fillMaterial(t_mat *mat, char type, t_vec color);

#endif
