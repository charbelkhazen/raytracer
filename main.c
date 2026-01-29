//TODO: change render function. should take as input scene
//NOTE: Code assummes only 1 scene: because of pars_checkCounts() function 
#include "parser.h"
#include "scene.h"
#include "ui.h"
#include "error.h"
#include "render.h"
#include <fcntl.h>

int main(void)
{
	int	file_descriptor;
	t_scene scene;
	ui_mlxParams_t	mlx_params;

	file_descriptor  = open("minirt.rt", O_RDONLY); //TODO:handle failure in open 
	//TODO: HANDLE FD CLOSURE!!!!!!!

	while (pars_parseProgram(file_descriptor, &scene))
		err_writeStdErr("Wrong Format in .rt file", 1);
	if (ui_initMlx(&mlx_params, scene.cam.img.img_ratio, scene.cam.img.img_width, "MiniRT"))
        	return err_msgReturnOne("MLX init failed");
	render_logicToMlx(&mlx_params, &scene.cam, &scene.univ, &scene.light);

	ui_mlxRender(&mlx_params);

	return (0);
}
