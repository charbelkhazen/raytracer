#include "ui.h"
#include "camera.h"

void	render_logicToMlx(ui_mlxParams_t *p, t_cam *cam) //take world also??
{
	int	y;
	int	x;
	int	height;
	int	width;
	t_vec	pixel;
	
	height = p->height;
	width = p->width;
	y = 0;
	while (y < height)
	{
		ui_remLinesErrMsg(height - y); // mv ui_rem... here as static
		x = 0;
		while (x < width)
		{
			//throw ray -> using x and y
			//color pixel -> color(ray, world);
				// color(ray, world) : uses hit, uses list of objects
			//then after finding the color of ray at (x,y):
			//use ui_drawpixel (move it here as a static function) : takes mlx param, pixel color and x and y (all good)
			x ++;
		}
		y ++;
	}
	err_writeStdErr("Done\n", 1);
}
