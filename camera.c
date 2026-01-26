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
# include "viewer.h"
# include "image.h"

static void	geom_setLookAtFrom(t_geom *geom, t_viewer view)
{
	vec_subs(&geom->lookat_to_lookfrom, &view.lookfrom, &view.lookat); 
}

static void	geom_setFocalDist(t_geom *geom)
{
	geom->focal_dist = vec_vectorLen(&geom->lookat_to_lookfrom);
}

static void	geom_setScreenDim(t_geom *geom, t_viewer view, t_img img)
{
	double theta;
	double h;

	theta = view.hfov * M_PI / 180.0;
	h = tan(theta / 2.0);
	
	geom->screen_width = h * geom->focal_dist * 2;
	geom->screen_height  = geom->screen_width *((double)img.img_height / img.img_width);
}

static void	geom_setOrthobasis(t_geom *geom, t_viewer view)
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

static void	geom_setPixelDeltas(t_geom *geom, t_img img)
{
	vec_scale(&geom->pix_delta_u, 1.0 / img.img_width,  &geom->screen_u);
	vec_scale(&geom->pix_delta_v, 1.0 / img.img_height, &geom->screen_v);
}

static void	geom_setScreenOrigin(t_geom *geom, t_viewer view)
{
	t_vec along_focal;
	t_vec half_u;
	t_vec half_v;
	t_vec tmp;

	vec_scale(&along_focal, geom->focal_dist, &geom->orthobasis_w);
	vec_scale(&half_u, 0.5, &geom->screen_u);
	vec_scale(&half_v, 0.5, &geom->screen_v);

	//screen00_loc = center - focal_distance * w - 0.5 * (screen_u + screen_v)
	vec_add(&tmp, &along_focal, &half_u);
	vec_add(&tmp, &tmp, &half_v);
	vec_subs(&geom->screen00_loc, &view.lookfrom, &tmp);
}

static void	geom_setPixel00(t_geom *geom)
{
	t_vec tmp;

	vec_add(&tmp, &geom->pix_delta_u, &geom->pix_delta_v);
	vec_scale(&tmp, 0.5, &tmp);
	vec_add(&geom->pix00_loc, &geom->screen00_loc, &tmp);
}

static void	geom_fill(t_geom *geom, t_viewer view, t_img img)
{
	geom_setLookAtFrom(geom, view);
	geom_setFocalDist(geom);
	geom_setScreenDim(geom, view, img);
	geom_setOrthobasis(geom, view);
	geom_setScreenVectors(geom);
	geom_setPixelDeltas(geom, img);
	geom_setScreenOrigin(geom, view);
	geom_setPixel00(geom); 
}

void	cam_fillCam(t_cam *cam, t_img img, t_viewer view)
{
	cam->img = img;
	cam->view = view;
	geom_fill(&cam->geom, view, img);
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
