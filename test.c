#include "universe.h"
#define	NUM_OBJ 100
#include "object.h"
# include "vector.h"
#include "sphere.h"

#include <stdio.h>
int main()
{

	t_vec	origin;

	vec_centerVec(&origin);

	t_sph sphere1;
	t_vec	center1;

	vec_fillVec(&center1, 10, 10, 10);
	sph_fillSph(&sphere1, center1, 2);

	t_sph sphere2;
	t_vec	center2;

	vec_fillVec(&center2, 30, 30, 30);
	sph_fillSph(&sphere2, center2, 10);

	t_univ	univ;
	t_obj	obj_lst[NUM_OBJ];
	
	univ_init(&univ, obj_lst, NUM_OBJ);

	univ_add(&univ, (t_obj *)&sphere1);
	univ_add(&univ, (t_obj *)&sphere2);

	t_ray ray;
	t_vec ray_dir;

	vec_fillVec(&ray_dir, 1, 1, 1);
	ray_fillRay(&ray, &origin, &ray_dir);
	
	t_hitRec rec; //DOES IT MAKE SENSE TO HAVE REC AS AN INPUT
	univ_throwRay(&ray, &univ, &rec);
}
