#include "camera.h"
#include "vector.h"
#include "stdlib.h"

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
