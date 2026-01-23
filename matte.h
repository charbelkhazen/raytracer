#ifndef MATTE_H
#define MATTE_H
#include "material.h"

typedef struct s_matte
{
	material_type type;
}	t_matte;

void	matte_fillMatte(t_matte *matte, material_type type);
#endif
