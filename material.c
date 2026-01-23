#include "material.h"
#include "matte.h"

//I am able to implement such function bcz all materials only take type.
//if each had its own inputs -> cannot unify them in one fill function
void	mat_fillMat(t_mat *mat, material_type type)
{
	if (type == MATTE_TYPE)
		matte_fillMatte(mat, type);
	//should have othetr ifs for all types of materials - TO BE IMPLEMENTED
}
