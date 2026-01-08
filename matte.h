#ifndef MATTE_H
#define MATTE_H
# include "material.h"

typedef struct s_matte
{
	t_material	*material;	
	t_vec	color;
}	t_matte;

#endif
