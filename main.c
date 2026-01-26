//TODO: change render function. should take as input scene

#include "scene.h"

int main(void)
{
	t_scene scene;

	univ_init(&scene.univ);

	//creating an object
	t_obj   obj1;
	t_shape shape1;
	t_vec	center1;
	t_mat   mat1;
	double	radius;
	t_vec	color;
	radius = 1.0;
	vec_fillVec(&center1, 0, 0, -5);
	shape_fillSphere(&shape1, center1, radius);
	mat_fillMatte(&mat1, 0);
	vec_fillVec(&color, 1, 1, 0);
	obj_fillObj(&obj1, shape1, mat1, color);

	//adding the obj to universe
	univ_addObj(&scene.univ, obj1);
	//let's contempt ourselves with one object in universe for now

	//init light
	t_vec	lightcoord;
	t_vec	lightcol;
	vec_fillVec(&lightcoord, 8, 15, -1);
	vec_fillVec(&lightcol, 1, 1, 1);
	light_fill(&scene.light, lightcoord, lightcol, 1);

	//init ambient 
	t_vec	ambientcol;
	double	ambientratio;

	ambientratio = 0.1;
	vec_fillVec(&ambientcol, 1, 1, 1);
	al_fill(&scene.ambient, ambientratio, ambientcol);

	/*int cam*/
	t_img	img;
	double	img_ratio;
	double	img_width;
	img_ratio = 16.0 / 9.0;
	img_width = 900;
	img_fill(&img, img_width, img_ratio);

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

	cam_fillCam(&scene.cam, img, view);

	return (0);
}

/*
ui_mlxParams_t mlx_params;


if (ui_initMlx(&mlx_params, img_ratio, img_width, "MiniRT")) // take advantage of setting img struct
	return err_msgReturnOne("MLX init failed");

render_logicToMlx(&mlx_params, &scene);

ui_mlxRender(&mlx_params);
*/
