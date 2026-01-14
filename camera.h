#ifndef CAMERA_H
#define CAMERA_H
# include "vector.h"
# include "ray.h"
# include "sphere.h"
# include "universe.h"
# include "light.h"

typedef struct s_cam
{
	t_vec	center;
	double	focal_dist;
	double	img_ratio;
	int	img_width;
	int	img_height;
	double	hfov;
	double	screen_height;
	double	screen_width;
	t_vec	screen_u;
	t_vec	screen_v;
	t_vec	screen00_loc;
	t_vec	pix00_loc;
	t_vec	pix_delta_u;
	t_vec	pix_delta_v;
	
}	t_cam;

void	cam_fillCam(t_cam *cam, double img_ratio, int img_width);

void	cam_throwRay(t_ray *ray, t_cam *cam, int pixel_i, int pixel_j);

//temporary function - needs modif
void	cam_rayColor(t_vec *color, t_ray *ray, t_univ *univ, t_light *light); // hit record should  be part of ray? 
#endif
