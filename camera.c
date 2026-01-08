#include "camera.h"
#include "vector.h"
#include "stdlib.h"
#include "ray.h"
#include "sphere.h"
#include "object.h"

static void	cam_assertion(double img_ratio, int img_width)
{
	std_assert(img_ratio > 0);
	std_assert(img_width > 0);
}

static void	cam_setImageDim(t_cam *cam, double img_ratio, int img_width)
{
	cam->img_ratio  = img_ratio;
	cam->img_width  = img_width;
	cam->img_height = (int)((double)img_width / img_ratio);
	if (cam->img_height < 1)
		cam->img_height = 1;
}

static void	cam_setScreen(t_cam *cam)
{
	cam->focal_dist    = 1.0;
	cam->screen_height = 2.0;
	cam->screen_width  = cam->screen_height *((double)cam->img_width / cam->img_height);
	vec_fillVec(&cam->screen_u, cam->screen_width, 0, 0);
	vec_fillVec(&cam->screen_v, 0, -cam->screen_height, 0);
}

static void cam_setPixelDeltas(t_cam *cam)
{
	vec_scale(&cam->pix_delta_u, 1.0 / cam->img_width,  &cam->screen_u);
	vec_scale(&cam->pix_delta_v, 1.0 / cam->img_height, &cam->screen_v);
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

	vec_subs(&tmp, &along_focal, &half_u);
	vec_subs(&tmp, &tmp, &half_v);
	vec_subs(&cam->screen00_loc, &cam->center, &tmp);
}

static void cam_setPixel00(t_cam *cam)
{
	t_vec tmp;

	vec_add(&tmp, &cam->pix_delta_u, &cam->pix_delta_v);
	vec_scale(&tmp, 0.5, &tmp);
	vec_add(&cam->pix00_loc, &cam->screen00_loc, &tmp);
}

void cam_fillCam(t_cam *cam, double img_ratio, int img_width)
{
	cam_assertion(img_ratio, img_width);
	cam_setImageDim(cam, img_ratio, img_width);
	cam_setScreen(cam);
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
//MUST MODIFIED
void	cam_rayColor(t_vec *color, t_ray *ray, t_sphere *sphere)
{
	t_hitRec	rec;

	if (sph_hit(sphere, ray, -9999, 99999, &rec))
		vec_fillVec(color, 255, 255, 255);
	else
		vec_fillVec(color, 0, 0, 0);
}
