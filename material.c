#include "material.h"
#include "matte.h"

void	mat_fillMatte(t_mat *mat, int onoff)
{
	mat->type = MATTE_TYPE;
	matte_fillMatte(&mat->as.matte, onoff);
}
