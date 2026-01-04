#include "./minilibx-linux/mlx.h"
#include "ui.h"
#include "error.h"
#include "stdlib.h"
#include "vector.h"

static void ui_remLinesErrMsg(int remaining_lines)
{
	char	str[100];

	std_itoa(str, remaining_lines); 
	err_writeStdErr("Remaining lines ", 3, str, "\n");
}

static void ui_drawpixel(ui_mlxParams_t *p, t_vec *pixel, int x, int y)
{
	int	red;
	int	green;
	int	blue;
	int	color;

	red = (int)(255.999 * pixel->x);
	green = (int)(255.999 * pixel->y);
	blue = (int)(255.999 * pixel->z);
	color = (red << 16) | (green << 8) | blue;
	*(unsigned int *)(p->buf + y * p->line_len + x * (p->bpp / 8)) = color;
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
		ui_remLinesErrMsg(height - y);
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
