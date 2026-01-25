#ifndef MATERIAL_H
#define MATERIAL_H

#include "matte.h"

typedef enum
{
	MATTE_TYPE
	//METALLIC_TYPE;
	//GLASS_TYPE;
}	material_type;


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
