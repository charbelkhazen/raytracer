#ifndef HIT_RECORD_H
#define HIT_RECORD_H

typedef struct s_obj {
	int	obj_shapeType;
	void	*obj_shape;
	int	obj_matType;
	void	*obj_mat;
}	t_obj;

void	obj_fillObj(t_obj *obj, int obj_shapeType, void *obj_shape, int obj_matType, void *obj_mat);
#endif
