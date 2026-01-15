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

void	img_fill(t_img *img, int img_width, double img_ratio)
{
	img->img_width = img_width;
	img->img_ratio = img_ratio;
	img->img_height = (int)((double)img_width / img_ratio);
	if (img->img_height < 1)
		img->img_height = 1;
}

static void	geom_setLookAtFrom(t_geom *geom, t_viewer view)
{
	vec_subs(&geom->lookat_to_lookfrom, &view.lookfrom, &view.lookat); 
}

static void	geom_setFocalDist(t_geom *geom)
{
	geom->focal_dist = vec_vectorLen(&geom->lookat_to_lookfrom);
}

static void	geom_set_screenDim(t_geom *geom, t_viewer view, t_img img)
{
	double theta;
	double h;

	theta = view.hfov * M_PI / 180.0;
	h = tan(theta / 2.0);
	
	geom->screen_width = h * geom->focal_dist * 2;
	geom->screen_height  = geom->screen_width *((double)img.img_height / img.img_width);
}

static void	geom_set_othobasis(t_geom *geom, t_viewer view)
{
	vec_unitVector(&geom->orthobasis_w, &geom->lookat_to_lookfrom);

	vec_cross(&geom->orthobasis_u, &view.vup, &geom->orthobasis_w);
	vec_unitVector(&geom->orthobasis_u, &geom->orthobasis_u);

	vec_cross(&geom->orthobasis_v, &geom->orthobasis_w, &geom->orthobasis_u);
}

static void	geom_setScreenVectors(t_geom *geom)
{
	vec_scale(&geom->screen_u, geom->screen_width, &geom->orthobasis_u);
	vec_scale(&geom->screen_v, -geom->screen_height, &geom->orthobasis_v);
}

static void	cam_setScreen(t_cam *cam, t_viewer view)
{
	double	theta;
	double	h;
	double	focal_dist;
	t_vec	lookfrom_to_lookat;

	//cam->focal_dist    = 1.0;
	vec_subs(&lookfrom_to_lookat, &view.lookfrom, &view.lookat); 
	focal_dist = vec_vectorLen(&lookfrom_to_lookat);

	theta = view.hfov * M_PI / 180.0;
	h = tan(theta / 2.0);
	
	cam->geom.screen_width = h * focal_dist * 2;
	cam->geom.screen_height  = cam->geom.screen_width *((double)cam->img.img_height / cam->img.img_width);

	//calculate u, v ,w unit basis
	t_vec	w;
	t_vec	u;
	t_vec	v;

	vec_unitVector(&w, &lookfrom_to_lookat);

	vec_cross(&u, &view.vup, &w);
	vec_unitVector(&u, &u);

	vec_cross(&v, &w, &u);
	//Calculate the vectors across the horizontal and down the vertical viewport edges.
	vec_scale(&cam->geom.screen_u, cam->geom.screen_width, &u);
	vec_scale(&cam->geom.screen_v, -cam->geom.screen_height, &v);
}

static void cam_setPixelDeltas(t_cam *cam)
{
	vec_scale(&cam->geom.pix_delta_u, 1.0 / cam->img.img_width,  &cam->geom.screen_u);
	vec_scale(&cam->geom.pix_delta_v, 1.0 / cam->img.img_height, &cam->geom.screen_v);
}

static void cam_setScreenOrigin(t_cam *cam, t_viewer view)
{
	t_vec along_focal;
	t_vec half_u;
	t_vec half_v;
	t_vec tmp;

	/*this is repetitive - I am getting the focal dist and u v w should be refactored */
	t_vec	lookfrom_to_lookat;
	double	focal_dist;
	vec_subs(&lookfrom_to_lookat, &view.lookfrom, &view.lookat); 
	focal_dist = vec_vectorLen(&lookfrom_to_lookat);

	//calculate w unit basis
	t_vec	w;

	vec_unitVector(&w, &lookfrom_to_lookat);
	/*will delete upper part*/

	vec_scale(&along_focal, focal_dist, &w);
	vec_scale(&half_u, 0.5, &cam->geom.screen_u);
	vec_scale(&half_v, 0.5, &cam->geom.screen_v);

	//screen00_loc = center - focal_distance * w - 0.5 * (screen_u + screen_v)
	vec_add(&tmp, &along_focal, &half_u);
	vec_add(&tmp, &tmp, &half_v);
	vec_subs(&cam->geom.screen00_loc, &view.lookfrom, &tmp);
}

static void cam_setPixel00(t_cam *cam)
{
	t_vec tmp;

	vec_add(&tmp, &cam->geom.pix_delta_u, &cam->geom.pix_delta_v);
	vec_scale(&tmp, 0.5, &tmp);
	vec_add(&cam->geom.pix00_loc, &cam->geom.screen00_loc, &tmp);
}

void	cam_fillCam(t_cam *cam, t_img img, t_viewer view)
{
	cam->img = img;
	cam->view = view;
	cam_setScreen(cam, view);
	cam_setPixelDeltas(cam);
	cam_setScreenOrigin(cam, view);
	cam_setPixel00(cam);
}

static void	cam_choosePixel(t_vec *pixel, t_cam *cam, int pixel_i, int pixel_j)
{
	t_vec	x_pos;
	t_vec	y_pos;
	
	//x_pos = i * pixel_delta_u (same for y_pos with j)
	vec_scale(&x_pos, (double)pixel_i, &cam->geom.pix_delta_u);
	vec_scale(&y_pos, (double)pixel_j, &cam->geom.pix_delta_v);
	//chosen pixel = pix00_loc + x_pos + y_pos (but done in two steps)
	vec_add(pixel, &x_pos, &y_pos);
	vec_add(pixel, pixel, &cam->geom.pix00_loc); 
}

static void	cam_throwRayOnPixel(t_ray *ray, t_vec *chosen_pixel, t_cam *cam)
{
	//ray orig = coordinates of camera center
	vec_fillVec(&ray->orig, cam->view.lookfrom.x, cam->view.lookfrom.y, cam->view.lookfrom.z);

	//ray direction found then normalized
	vec_subs(&ray->dir, chosen_pixel, &cam->view.lookfrom);
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
