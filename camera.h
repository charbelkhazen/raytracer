#ifndef CAMERA_H
#define CAMERA_H
# include "vector.h"
# include "ray.h"
# include "sphere.h"
# include "universe.h"
# include "light.h"
//# include "viewer.h"


typedef struct s_viewer
{
	t_vec	lookfrom;
	t_vec	lookat;
	t_vec	vup; //vector that defines x and y on plane orth. to look_at dir
	double	hfov;
}	t_viewer;

void	viewer_fill(t_viewer *viewer, t_vec vup, t_vec lookfrom, t_vec lookat, double hfov);

typedef	struct	s_img
{
	int	img_width;
	int	img_height;
	double	img_ratio;
}	t_img;

void	img_fill(t_img *img, int img_width, double img_ratio);

typedef	struct s_geom
{
	double	screen_height; 
	double	screen_width;
	t_vec	screen_u;
	t_vec	screen_v;
	t_vec	screen00_loc;
	t_vec	pix00_loc;
	t_vec	pix_delta_u;
	t_vec	pix_delta_v;
}	t_geom;

typedef struct s_cam
{
	t_vec	center; // rm
	double	focal_dist; // rm
	t_img	img;
	t_viewer view;
	t_geom	geom;
}	t_cam;

void	cam_fillCam(t_cam *cam, t_img img, t_viewer view);

void	cam_throwRay(t_ray *ray, t_cam *cam, int pixel_i, int pixel_j);

//sould be in render!!!
//temporary function - needs modif
void	cam_rayColor(t_vec *color, t_ray *ray, t_univ *univ, t_light *light); // hit record should  be part of ray? 
#endif
