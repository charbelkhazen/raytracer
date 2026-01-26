#ifndef CAMERA_H
#define CAMERA_H

# include "vector.h"
# include "ray.h"
# include "sphere.h" // remove when cam_rayCOlor is moved
# include "universe.h"// remove when cam_rayCOlor is moved
# include "light.h"// remove when cam_rayCOlor is moved
# include "viewer.h"
# include "image.h"

typedef	struct s_geom
{
	//not normalized
	t_vec	lookat_to_lookfrom;

	t_vec	orthobasis_w;
	t_vec	orthobasis_u;
	t_vec	orthobasis_v;

	double	focal_dist;

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
	t_img	img;
	t_viewer view;
	t_geom	geom;
}	t_cam;

//assumes img and view are already filled. Dot not pass undefined view and img
void	cam_fillCam(t_cam *cam, t_img img, t_viewer view);

void	cam_throwRay(t_ray *ray, t_cam *cam, int pixel_i, int pixel_j);

//sould be in render!!!
//temporary function - needs modif
void	cam_rayColor(t_vec *color, t_ray *ray, t_univ *univ, t_light *light); // hit record should  be part of ray? 
#endif
