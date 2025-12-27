#include "ui.h"
#include "error.h"

int main(void)
{
	ui_mlxParams_t mlx_params;

	if (ui_initMlx(&mlx_params, 256, 256, "MiniRT"))
        	return err_msgReturnOne("MLX init failed");
	ui_buildImg(&mlx_params);
	ui_mlxRender(&mlx_params);
}
