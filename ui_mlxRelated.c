#include "./minilibx-linux/mlx.h"
#include "ui.h"
#include "error.h"
#include "stdlib.h"
#include "vector.h"
#include <X11/keysym.h>
#include <stdlib.h>

int	ui_initMlx(ui_mlxParams_t *p, double ratio, int w, char *ttl)
{
	int	h;
	
	std_assert(ratio > 0);
	std_assert(w > 0);
	h = (int)(w / ratio);
	if (h < 1)
		h = 1;
	p->mlx = mlx_init();
	p->width = w;
	p->height = h;
	p->win = mlx_new_window(p->mlx, w, h, ttl);
	p->img = mlx_new_image(p->mlx, w, h);
	p->buf = mlx_get_data_addr(p->img, &p->bpp, &p->line_len, &p->endian);
	return (!(p->mlx && p->img && p->buf));
}

int	key_hook(int keycode, void *params)
{ 
	ui_mlxParams_t *mlx_params;

	mlx_params = ((ui_mlxParams_t *)params);
	if (keycode == 'q' || keycode == XK_Escape)
	{
		mlx_destroy_window(mlx_params->mlx, mlx_params->win); 
		mlx_loop_end(mlx_params->mlx);
	}
	return (0);
}

int on_close(void *params)
{
	ui_mlxParams_t *mlx_params;

	mlx_params = ((ui_mlxParams_t *)params);
	mlx_destroy_window(mlx_params->mlx, mlx_params->win); 
	mlx_loop_end(mlx_params->mlx);
	return (0);
}

void	ui_mlxRender(ui_mlxParams_t *p)
{
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_key_hook(p->win, key_hook, p);
	mlx_hook(p->win, 17, 0, on_close, p);
	mlx_loop(p->mlx);
}
