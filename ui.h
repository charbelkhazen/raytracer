#ifndef UI_H
#define UI_H

typedef struct ui_mlxParams_s
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int	bpp;
	int	line_len;
	int	endian;
	int	width;
	int	height;
}	ui_mlxParams_t;

int	ui_initMlx(ui_mlxParams_t *params, int width, int height, char *title);

void	ui_buildImg(ui_mlxParams_t* params);

void	ui_mlxRender(ui_mlxParams_t *params);
#endif

/*
int main(void)
{
	ui_mlxParams_t mlx_params;

	if (ui_initMlx(&mlx_params, 256, 256, "MiniRT"))
        	return err_msgReturnOne("MLX init failed");
	ui_buildImg(&mlx_params);
	ui_mlxRender(&mlx_params);
}
*/
