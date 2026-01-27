#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "universe.h"
#include "light.h"
#include "ambientlight.h"

//univ refers to the "universe of objects"
typedef struct s_scene
{
	t_cam		cam;
	t_univ		univ;
	t_light		light;
	t_ambientLight ambient;
	t_img		img;

}	t_scene;
	
#endif
