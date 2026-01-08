#include "ui.h"
#include "error.h"
#include "render.h"
#include "camera.h"

int main(void)
{
	double img_ratio;
	double img_width;
	ui_mlxParams_t mlx_params;
	t_cam	cam;

	img_ratio = 16.0 / 9.0;
	img_width = 900;

	if (ui_initMlx(&mlx_params, img_ratio, img_width, "MiniRT"))
        	return err_msgReturnOne("MLX init failed");

	cam_fillCam(&cam, img_ratio, img_width);

	render_logicToMlx(&mlx_params, &cam);

	ui_mlxRender(&mlx_params);

	return (0);
}
