#include "camera.h"
#include "vector.h"
#include "stdlib.h"
#include "ray.h"
#include "sphere.h"
#include "object.h"
#include "universe.h"
#include "intersection.h"
#include "lambertphong.h"
# include <math.h>
//# include "viewer.h"

void	viewer_fill(t_viewer *viewer, t_vec vup, t_vec lookfrom, t_vec lookat, double hfov)
{
	viewer->lookat = lookat;
	viewer->lookfrom = lookfrom;
	viewer->vup = vup;
	viewer->hfov = hfov;
}

static void	cam_assertion(double img_ratio, int img_width)
{
	std_assert(img_ratio > 0);
	std_assert(img_width > 0);
}

static void	cam_setImageDim(t_cam *cam, double img_ratio, int img_width)
{
	cam->img.img_ratio  = img_ratio;
	cam->img.img_width  = img_width;
	cam->img.img_height = (int)((double)img_width / img_ratio);
	if (cam->img.img_height < 1)
		cam->img.img_height = 1;
}

static void	cam_setScreen(t_cam *cam, double hfov)
{
	double	theta;
	double	h;

	cam->focal_dist    = 1.0;

	theta = hfov * M_PI / 180.0;
	h = tan(theta / 2.0);
	cam->screen_width = h * cam->focal_dist * 2;
	cam->screen_height  = cam->screen_width *((double)cam->img.img_height / cam->img.img_width);
	vec_fillVec(&cam->screen_u, cam->screen_width, 0, 0);
	vec_fillVec(&cam->screen_v, 0, -cam->screen_height, 0);
}

static void cam_setPixelDeltas(t_cam *cam)
{
	vec_scale(&cam->pix_delta_u, 1.0 / cam->img.img_width,  &cam->screen_u);
	vec_scale(&cam->pix_delta_v, 1.0 / cam->img.img_height, &cam->screen_v);
}

static void cam_setScreenOrigin(t_cam *cam)
{
	t_vec along_focal;
	t_vec half_u;
	t_vec half_v;
	t_vec tmp;

	vec_fillVec(&cam->center, 0, 0, 0);
	vec_fillVec(&along_focal, 0, 0, cam->focal_dist);
	vec_scale(&half_u, 0.5, &cam->screen_u);
	vec_scale(&half_v, 0.5, &cam->screen_v);

	//screen00_loc = center - (0,0, focal_dist) - 0.5 * (screen_u + screen_v)
	vec_add(&tmp, &along_focal, &half_u);
	vec_add(&tmp, &tmp, &half_v);
	vec_subs(&cam->screen00_loc, &cam->center, &tmp);
}

static void cam_setPixel00(t_cam *cam)
{
	t_vec tmp;

	vec_add(&tmp, &cam->pix_delta_u, &cam->pix_delta_v);
	vec_scale(&tmp, 0.5, &tmp);
	vec_add(&cam->pix00_loc, &cam->screen00_loc, &tmp);
}

void	cam_fillCam(t_cam *cam, double img_ratio, int img_width, t_viewer view)
{
	cam_assertion(img_ratio, img_width);
	cam_setImageDim(cam, img_ratio, img_width);
	cam_setScreen(cam, view.hfov);
	cam_setPixelDeltas(cam);
	cam_setScreenOrigin(cam);
	cam_setPixel00(cam);
}

static void	cam_choosePixel(t_vec *pixel, t_cam *cam, int pixel_i, int pixel_j)
{
	t_vec	x_pos;
	t_vec	y_pos;
	
	//x_pos = i * pixel_delta_u (same for y_pos with j)
	vec_scale(&x_pos, (double)pixel_i, &cam->pix_delta_u);
	vec_scale(&y_pos, (double)pixel_j, &cam->pix_delta_v);
	//chosen pixel = pix00_loc + x_pos + y_pos (but done in two steps)
	vec_add(pixel, &x_pos, &y_pos);
	vec_add(pixel, pixel, &cam->pix00_loc); 
}

static void	cam_throwRayOnPixel(t_ray *ray, t_vec *chosen_pixel, t_cam *cam)
{
	//ray orig = coordinates of camera center
	vec_fillVec(&ray->orig, cam->center.x, cam->center.y, cam->center.z);

	//ray direction found then normalized
	vec_subs(&ray->dir, chosen_pixel, &cam->center);
	vec_unitVector(&ray->dir, &ray->dir);
}

void	cam_throwRay(t_ray *ray, t_cam *cam, int pixel_i, int pixel_j)
{
	t_vec	chosen_pixel;

	cam_choosePixel(&chosen_pixel, cam, pixel_i, pixel_j);
	cam_throwRayOnPixel(ray, &chosen_pixel, cam);
}

//naive color function - sphere hit other
#include <stdio.h>
void	cam_rayColor(t_vec *color, t_ray *ray, t_univ *univ, t_light *light)
{
	t_hitRec	rec;

	if (univ_hit(ray, univ, &rec)) //assumes tmin/max defined in throwray only
	{
		//*color = rec.material.color;
		//*color = rec.normal;
		lp_shade(color, rec, *light, *univ, *ray);
	}
	else
		vec_fillVec(color, 0, 0, 0);
}
