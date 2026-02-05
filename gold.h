#ifndef GOLD_H
#define GOLD_H

# include "vector.h"

typedef struct s_gold
{
	t_vec	albedo;
	double	roughness; // [0,1] range
}	t_gold;

#endif
