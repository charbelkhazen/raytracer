#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "vector.h"
#include "material.h"

typedef struct s_hitRec { //seperate it  (other module - intersection != object definition)
	t_vec	p;
	t_vec	normal; // NEED TO SEE HOW
	t_mat	material;
	double t;
}	t_hitRec;

typedef struct s_obj {
	int	obj_shapeType;
	void	*obj_shape;
	int	obj_matType;
	void	*obj_mat;
}	t_obj;

void	obj_fillObj(t_obj *obj, int obj_shapeType, void *obj_shape, int obj_matType, void *obj_mat);
#endif
