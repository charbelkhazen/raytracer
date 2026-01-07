#include "camera.h"
#include "vector.h"
#include "stdlib.h"

void	cam_fillCam(t_cam *cam, double img_ratio, int img_width)
{
	std_assert(img_ratio > 0);
	std_assert(img_width > 0);

	cam->focal_dist = 1; //setting

	cam->img_ratio = img_ratio;
	cam->img_width = img_width;
	cam-> img_height = (int)(img_width / img_ratio);
	if (cam->img_height < 1)
		cam->img_height = 1;
	
	cam->screen_height = 2; //setting
	cam->screen_width = cam->screen_height * (double)(cam->img_height / cam->img_height);
	vec_fillVec(cam->screen_u, cam->screen_width, 0, 0);
	vec_fillVec(cam->screen_v, 0, -cam->screen_height, 0);
	vec_scale(cam->pix_delta_u, screen_u, 1 / img_width);
	vec_scale(cam->pix_delta_v, screen_v, 1 / img_height);

	t_vec	along_focal;
	t_vec	half_screen_u;
	t_vec	half_screen_v;

	vec_fillVec(along_focal, 0, 0, focal_dist);
	vec_scale(half_screen_v, cam->screen_v, 1 / 2);
	vec_scale(half_screen_u, cam->screen_u, 1 / 2);

	vec_subs(cam->screen00_loc, cam->center, vec_subs(cam->screen00_loc, along_focal, vec_subs(cam->screen00_loc, half_screen_u, half_screen_v)));
	vec_add(cam->pix00_loc, cam->screen00_loc, vec_scale(cam->pix00_loc, 0.5, vec_add(cam->pix00_loc, pix_delta_u , pix_delta_v)));
}
// drawing functions
