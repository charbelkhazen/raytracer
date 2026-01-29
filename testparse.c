#include <stdio.h>
#include "scene.h"
#include "vector.h"
#include "camera.h"
#include "light.h"
#include "ambientlight.h"
#include "universe.h"
#include "object.h"
#include "shape.h"
#include "material.h"

/* ===================== BASIC ===================== */

void	dbg_vec(const char *name, t_vec v)
{
	printf("%s = (%.6f, %.6f, %.6f)\n", name, v.x, v.y, v.z);
}

/* ===================== AMBIENT ===================== */

void	dbg_ambient(t_ambientLight *a)
{
	printf("Ambient Light:\n");
	printf("  ratio = %.6f\n", a->ratio);
	dbg_vec("  color", a->color);
}

/* ===================== LIGHT ===================== */

void	dbg_light(t_light *l)
{
	printf("Light:\n");
	dbg_vec("  src", l->src);
	dbg_vec("  color", l->color);
	printf("  brightness = %.6f\n", l->bright);
}

/* ===================== MATERIAL ===================== */

void	dbg_material(t_mat *m)
{
	if (m->type == MATTE_TYPE)
	{
		printf("  Material: MATTE\n");
		printf("    onoff = %d\n", m->as.matte.onoff);
	}
	else
		printf("  Material: UNKNOWN (%d)\n", m->type);
}

/* ===================== SHAPE ===================== */

void	dbg_shape(t_shape *s)
{
	if (s->type == SPHERE_TYPE)
	{
		printf("  Shape: SPHERE\n");
		dbg_vec("    center", s->as.sphere.center);
		printf("    radius = %.6f\n", s->as.sphere.radius);
	}
	else
		printf("  Shape: UNKNOWN (%d)\n", s->type);
}

/* ===================== OBJECT ===================== */

void	dbg_object(int i, t_obj *obj)
{
	printf("Object #%d:\n", i);
	dbg_shape(&obj->shape);
	dbg_material(&obj->mat);
	dbg_vec("  color", obj->color);
}

/* ===================== UNIVERSE ===================== */

void	dbg_universe(t_univ *u)
{
	int i;

	printf("Universe:\n");
	printf("  object count = %d\n", u->count);
	for (i = 0; i < u->count; i++)
		dbg_object(i, &u->obj_lst[i]);
}

/* ===================== CAMERA ===================== */

void	dbg_camera(t_cam *c)
{
	printf("Camera:\n");

	/* Viewer */
	printf("  Viewer:\n");
	dbg_vec("    lookfrom", c->view.lookfrom);
	dbg_vec("    lookat",   c->view.lookat);
	dbg_vec("    vup",      c->view.vup);
	printf("    hfov = %.6f\n", c->view.hfov);

	/* Geometry */
	printf("  Geometry:\n");
	dbg_vec("    w", c->geom.orthobasis_w);
	dbg_vec("    u", c->geom.orthobasis_u);
	dbg_vec("    v", c->geom.orthobasis_v);

	printf("    focal_dist = %.6f\n", c->geom.focal_dist);
	printf("    screen_w   = %.6f\n", c->geom.screen_width);
	printf("    screen_h   = %.6f\n", c->geom.screen_height);

	dbg_vec("    pixel00", c->geom.pix00_loc);
	dbg_vec("    delta_u", c->geom.pix_delta_u);
	dbg_vec("    delta_v", c->geom.pix_delta_v);
}

/* ===================== SCENE ===================== */

void	dbg_scene(t_scene *s)
{
	if (!s)
	{
		printf("SCENE DEBUG: null pointer\n");
		return;
	}

	printf("\n========== SCENE DEBUG ==========\n\n");

	printf("[CAMERA]\n");
	dbg_camera(&s->cam);
	printf("\n");

	printf("[AMBIENT]\n");
	dbg_ambient(&s->ambient);
	printf("\n");

	printf("[LIGHT]\n");
	dbg_light(&s->light);
	printf("\n");

	printf("[UNIVERSE]\n");
	dbg_universe(&s->univ);
	printf("\n");

	printf("======== END SCENE DEBUG ========\n\n");
}




#include "parser.h"
#include <fcntl.h>
#include "get_next_line.h"
#include "scene.h"
int main()
{
	int	fd;
	t_scene	scene;

	fd = open("minirt.rt", O_RDONLY);

	printf("%d\n", pars_parseProgram(fd, &scene));

	dbg_scene(&scene);

	close(fd);
}

