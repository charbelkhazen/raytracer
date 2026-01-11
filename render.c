#include "ui.h"
#include "camera.h"
#include "stdlib.h"
# include "error.h"
# include "sphere.h"
# include "universe.h"

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

//idea
//throw ray -> using x and y
//color pixel -> color(ray, world);
	// color(ray, world) : uses hit, uses list of objects
//then after finding the color of ray at (x,y):
//use ui_drawpixel (move it here as a static function) : takes mlx param, pixel color and x and y (all good)

static void	render_throwThenColor(ui_mlxParams_t *p, t_cam *cam, t_univ *univ, int pixel_i, int pixel_j)
{
	t_ray	ray;
	t_vec	color;
	t_sph	sphere; //sphere and center sphere should be defined outside and passed as arguments in logic_to_mlx (world)
	t_vec	center_sphere;

	//temp
	vec_fillVec(&center_sphere, 0, 0, -10);
	sph_fillSph(&sphere, center_sphere, 5);

	//get ray for (i,j)
	cam_throwRay(&ray, cam, pixel_i, pixel_j);
	//get color for the ray
	cam_rayColor(&color, &ray, &sphere); // needs to be modified, here, its naive
	render_drawpixel(p, &color, pixel_i, pixel_j);
}

void	render_logicToMlx(ui_mlxParams_t *p, t_cam *cam, t_univ *univ) //take world also??
{
	int	y;
	int	x;
	int	height;
	int	width;

	height = cam->img_height;
	width = cam->img_width;
	y = 0;
	while (y < height)
	{
		render_remLinesErrMsg(height - y);
		x = 0;
		while (x < width)
		{
			render_throwThenColor(p, cam, univ, x, y);
			x ++;
		}
		y ++;
	}
	err_writeStdErr("Done\n", 1);
}
