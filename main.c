#include "ui.h"
#include "error.h"
#include "render.h"
#include "camera.h"

/* adding universe */
#include "universe.h"
#define	NUM_OBJ 100
#include "object.h"
# include "vector.h"
#include "sphere.h"
#include "material.h"

int main(void)
{
	/*adding universe*/
	t_vec	origin;

	vec_centerVec(&origin);

	t_sph sphere1;
	t_vec	center1;

	vec_fillVec(&center1, 0, 0, -5);
	sph_fillSph(&sphere1, center1, 1);

	t_sph sphere2;
	t_vec	center2;

	vec_fillVec(&center2, 2, 0, -8);
	sph_fillSph(&sphere2, center2, 2);
	
	t_mat mat;
	t_vec mat_color;

	vec_fillVec(&mat_color, 1, 1, 0); //? 1 or 255??
	mat_fillMaterial(&mat, 'm', mat_color);

	t_obj obj1;
	t_obj obj2;

	obj_fillObj(&obj1, 's', (void *)&sphere1, 'm', (void *)&mat);
	obj_fillObj(&obj2, 's', (void *)&sphere2, 'm', (void *)&mat);

	t_univ	univ;
	t_obj	obj_lst[NUM_OBJ];
	
	univ_init(&univ, obj_lst, NUM_OBJ);

	univ_add(&univ, &obj1);
	univ_add(&univ, &obj2);

	/*setting cam and mlx, calling render*/
	double img_ratio;
	double img_width;
	ui_mlxParams_t mlx_params;
	t_cam	cam;

	img_ratio = 16.0 / 9.0;
	img_width = 900;

	if (ui_initMlx(&mlx_params, img_ratio, img_width, "MiniRT"))
        	return err_msgReturnOne("MLX init failed");

	cam_fillCam(&cam, img_ratio, img_width);

	render_logicToMlx(&mlx_params, &cam, &univ);

	ui_mlxRender(&mlx_params);

	return (0);
}
