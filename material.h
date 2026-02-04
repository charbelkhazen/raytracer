#ifndef MATERIAL_H
#define MATERIAL_H

#include "matte.h"
#include "types.h"

typedef struct s_material
{
	material_type type;
	union
	{
		t_matte matte;
		//t_met metallic;
		//t_gl  glass;
	} as;
}	t_mat;

void	mat_fillMatte(t_mat *mat, int onoff);

#endif
