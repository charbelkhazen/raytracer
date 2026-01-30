#include "ui.h"
#include "stdlib.h"
# include "error.h"
#include "scene.h"
#include "lambertphong.h"

void	render_rayColor(t_vec *color, t_ray *ray, t_scene *scene)  //t_univ *univ, t_light *light)
{
	t_hitRec	rec;

	if (univ_hit(ray, &scene->univ, &rec)) //assumes tmin/max defined in throwray only
		lp_shade(color, &rec, &scene->light, &scene->univ, ray);
	else
		vec_fillVec(color, 0, 0, 0);
}

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

static void	render_throwThenColor(ui_mlxParams_t *p, t_scene *scene, int pixel_i, int pixel_j) // t_cam *cam, t_univ *univ, int pixel_i, int pixel_j, t_light *light)
{
	t_ray	ray;
	t_vec	color;

	//get ray for (i,j)
	cam_throwRay(&ray, &scene->cam, pixel_i, pixel_j);
	//get color for the ray
	render_rayColor(&color, &ray, scene); // needs to be modified, here, its naive
	render_drawpixel(p, &color, pixel_i, pixel_j);
}

//render_throwThenColor needs refactoring
void	render_logicToMlx(ui_mlxParams_t *p, t_scene *scene) //t_cam *cam, t_univ *univ, t_light *light)
{
	int	y;
	int	x;
	int	height;
	int	width;

	height = scene->cam.img.img_height;
	width = scene->cam.img.img_width;
	y = 0;
	while (y < height)
	{
		render_remLinesErrMsg(height - y);
		x = 0;
		while (x < width)
		{
			render_throwThenColor(p, scene, x, y);//&scene->cam, &scene->univ, x, y, &scene->light);
			x ++;
		}
		y ++;
	}
	err_writeStdErr("Done\n", 1);
}
