#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector.h"

typedef struct s_hitRec { //seperate it  (other module - intersection != object definition)
	t_vec	p;
	t_vec	normal;
	t_vec	color;
	int	shape;
	int	mat;
	double	t;
}	t_hitRec;

#endif
