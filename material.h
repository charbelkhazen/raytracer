#ifndef MATERIAL_H
#define MATERIAL_H

#include "matte.h"
#include "types.h"
#include "plastic.h"
#include "mirror.h"
#include "steel.h"
#include "gold.h"

typedef struct s_material
{
	material_type type;
	union
	{
		t_matte matte;
		t_plastic plastic;
		t_mirror mirror;
	} as;
}	t_mat;

void	mat_fillMatte(t_mat *mat, int onoff);

void	mat_fillPlastic(t_mat *mat, int onoff);

void	mat_fillMirror(t_mat *mat, int onoff);
#endif
