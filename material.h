#ifndef MATERIAL_H
#define MATERIAL_H

#include "matte.h" // uncomment when fixed

typedef enum
{
	MATTE_TYPE;
	//METALLIC_TYPE;
	//GLASS_TYPE;
}	material_type;


typedef struct s_material
{
	material_type type;
	union
	{
		t_mat matte;
		//t_met metallic;
		//t_gl  glass;
	} as;
}	t_mat;

void	mat_fillMat(t_mat *mat, int type);
#endif
