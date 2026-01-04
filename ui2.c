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

void	ui_buildImg(ui_mlxParams_t *p)
{
	int	y;
	int	x;
	int	height;
	int	width;
	//char	tmp_str[100];

	height = p->height;
	width = p->width;
	y = 0;
	while (y < height)
	{
	/*
		std_itoa(tmp_str, height - y); 
		err_writeStdErr("Remaining lines ", 3, tmp_str, "\n");
	*/
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
