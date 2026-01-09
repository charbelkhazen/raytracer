#include "ui.h"
#include "camera.h"
#include "stdlib.h"
# include "error.h"
# include "sphere.h"

static void render_remLinesErrMsg(int remaining_lines)
{
	char	str[100];

	std_itoa(str, remaining_lines); 
	err_writeStdErr("Remaining lines ", 3, str, "\n");
}

static void render_drawpixel(ui_mlxParams_t *p, t_vec *pixel, int x, int y)
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

void	render_logicToMlx(ui_mlxParams_t *p, t_cam *cam) //take world also??
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
		render_remLinesErrMsg(height - y);
		x = 0;
		while (x < width)
		{
			t_ray	ray;  // either defined above or in a new function with throwRay(...
			cam_throwRay(&ray, cam, x, y);
			t_vec	color; // !! either defined above or in a new function
			//sphere: maybe in world and world passed in arg of function
			t_sph sphere;
			t_vec	center_sphere;
			vec_fillVec(&center_sphere, 0, 0, -1);
			sph_fillSph(&sphere, center_sphere, 0.5);
			cam_rayColor(&color, &ray, &sphere); // needs to be modified, here, its naive
			render_drawpixel(p, &color, x, y);
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
