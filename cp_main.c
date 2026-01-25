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
#include "light.h"


//#include "viewer.h"

int main(void)
{
	/*adding universe*/
	t_univ	univ;
	univ_init(&univ);

	t_obj   obj1;
	t_shape shape1;
	t_vec	center1;
	t_mat   mat1;
	int	radius;
	t_vec	color;

	radius = 1;
	vec_fillVec(&center1, 0, 0, -5);
	shape_fillSphere(&shape1, center, radius);
	mat_fillMatte(&mat1, onoff);
	vec_fillVec(&color, 1, 1, 0);
	obj_fillObj(&obj1, shape1, mat1, color);


	univ_add(&univ, &obj1);

	t_light	light;
	t_vec	lightcoord;
	t_vec	lightcol;

	vec_fillVec(&lightcoord, 8, 15, -1);
	vec_fillVec(&lightcol, 1, 1, 1);
	light_fill(&light, lightcoord, lightcol, 1);


	/*setting cam and mlx, calling render*/
	ui_mlxParams_t mlx_params;
	t_cam	cam;

	/*setting img*/
	t_img	img;
	double	img_ratio;
	double	img_width;
	img_ratio = 16.0 / 9.0;
	img_width = 900;
	img_fill(&img, img_width, img_ratio);

	if (ui_initMlx(&mlx_params, img_ratio, img_width, "MiniRT")) // take advantage of setting img struct
        	return err_msgReturnOne("MLX init failed");

	/*view parameters*/
	t_viewer view;
	t_vec	lookfrom;
	t_vec	lookat;
	t_vec	vup;
	double	hfov;
	hfov = 90.0;
	vec_fillVec(&lookfrom, 0, 0, 0);
	vec_fillVec(&lookat, 0, 0, -1);
	vec_fillVec(&vup, 0, 1, 0);

	viewer_fill(&view, vup, lookfrom, lookat, hfov);

	//!insted of img_ratio and img_width. Fill them in t_img
	cam_fillCam(&cam, img, view);

	render_logicToMlx(&mlx_params, &cam, &univ, &light);

	ui_mlxRender(&mlx_params);

	return (0);
}
