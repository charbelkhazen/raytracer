#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector.h"
#include "material.h"

typedef struct s_hitRec { //seperate it  (other module - intersection != object definition)
	t_vec	p;
	t_vec	normal; // NEED TO SEE HOW
	t_mat	material;
	double	t;
}	t_hitRec;

#endif
