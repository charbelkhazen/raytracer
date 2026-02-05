#ifndef STEEL_H
#define STEEL_H

# include "vector.h"

typedef struct s_steel
{
	t_vec	albedo;
	double	roughness; // [0,1] range
}	t_steel;

#endif
