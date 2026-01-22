#ifndef PROGRAMPARAMS_H
#define PROGRAMPARAMS_H

#include "light.h"
#include "cam.h"
#include "ambient.h"
#include "managematerials.h"
#include "managespheres.h"

typedef struct s_rt_params
{
	t_light	light;
	t_cam	cam;
	t_ambientLight ambient;
	t_material_list material;
	t_sphere_list sphere;
	t_obj_list obj; // should be t_univ ?? 
	// still  need to add cylinder and plane and different materials
}	t_rt_params;

#endif
