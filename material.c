#include "material.h"
#include "vector.h"

void	mat_fillMaterial(t_mat *mat, char type, t_vec color)
{
	mat->type = type;
	mat->color = color;
}
