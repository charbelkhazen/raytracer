#ifndef CAMERA_H
#define CAMERA_H
# include "vector.h"

typedef struct s_cam
{
	t_vec	center;
	double	focal_dist;
	double	img_ratio;
	double	img_width;
	double	screen_height;
	double	screen_width;
	t_vec	screen_u;
	t_vec	screen_v;
	t_vec	pix00_loc;
	t_vec	pix_delta_u;
	t_vec	pix_delta_v;
	
}	t_cam;

#endif
