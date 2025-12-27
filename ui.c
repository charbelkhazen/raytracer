#include "./minilibx-linux/mlx.h"
#include "ui.h"
#include "error.h"
#include "libft.h"

int	ui_initMlx(ui_mlxParams_t *p, int w, int h, char *ttl)
{
    p->mlx = mlx_init();
    p->width = w;
    p->height = h;
    p->win = mlx_new_window(p->mlx, w, h, ttl);
    p->img = mlx_new_image(p->mlx, w, h);
    p->buf = mlx_get_data_addr(p->img, &p->bpp, &p->line_len, &p->endian);
    return (!(p->mlx && p->img && p->buf));
}

int	key_hook(int keycode, void *mlx)
{
	if (keycode == 'q')
		mlx_loop_end(mlx);
	return (0);
}

void	ui_mlxRender(ui_mlxParams_t *p)
{
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_key_hook(p->win, key_hook, p->mlx);
	mlx_loop(p->mlx);
}

void	ui_buildImg(ui_mlxParams_t *p)
{
	int	y;
	int	x;
	int	height;
	int	width;

	height = p->height;
	width = p->width;
	y = 0;
	while (y < height)
	{
		err_writeStdErr("Remaining lines ", 3, ft_itoa(height - y), "\n");
		x = 0;
		while (x < width)
		{
		    double r = (double)x / (width - 1);
		    double g = (double)y / (height - 1);
		    double b = 0.0;

		    int ir = (int)(255 * r); //255.999
		    int ig = (int)(255 * g);
		    int ib = (int)(255 * b);

		    int color = (ir << 16) | (ig << 8) | ib;
		    *(unsigned int *)(p->buf + y * p->line_len + x * (p->bpp / 8)) = color;
		    x ++;
		}
		y ++;
	}
	err_writeStdErr("Done\n", 1);
}
