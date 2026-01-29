here are more functions added to the parser implementation

can you tell me if it has errors


#include "get_next_line.h"

//has two modes : check duplicates mode (mode 0) and check basic setup (mode 1)
// on mode = 0 returns 1 if count light or camera or ambient > 1 and 0 otherwise
//on mode = 1 returns 1 if NOT COMPLETE. in mode1 , inputing type has no sense, you can thus write anything in the type field, For cleanness input "type = 0"
static int	pars_checkCounts(t_cmd_type type, int mode)
{
	static int	count_camera = 0;
	static int	count_light = 0;
	static int	count_ambient = 0;
	static int	count_obj = 0;

	if (type == CAMERA_CMD)
		count_camera++;
	else if (type == AMBIENT_CMD)
		count_ambient++;
	else if (type == LIGHT_CMD)
		count_light++;
	else if (type == SPHERE_CMD || type == PLANE_CMD || type == CYLINDER_CMD)
		count_obj++;
	
	//mode = 0 -> Check duplicates
	if (!mode)
	{
		if (count_light > 1 || count_camera > 1 || count_ambient > 1)
			return (1)
		return (0);
	}
	//mode == 1 -> Basic setup completeness check
	if (!count_light || !count_camera || !count_ambient || !count_obj)
		return (1);
	return (0);
	
}

static void	pars_setDefaultImg(t_scene *scene)
{
	double	img_ratio;
	double	img_width;

	img_ratio = 16.0 / 9.0;
	img_width = 900;
	img_fill(&scene.cam.img, img_width, img_ratio);
}

int	pars_fillScene(t_scene *scene, t_parsables *parsables, t_cmd_type cmdtype)
{
	if (cmdtype == CAMERA_CMD)
	{
		pars_setDefaultImg(scene);
		cam_fillCam(&scene->cam, scene->img, parsables->view);
	}
	else if (cmdtype == SPHERE_CMD) // TODO : DO THE SAME WITH CYL AND PLANE
	{
		univ_init(&scene.univ);
		univ_addObj(&scene.univ, parsables->obj);
	}
	else if (cmdtype == LIGHT_CMD)
		scene->light = parsables->light;
	else if (cmdtype == AMBIENT_CMD)
		scene -> ambient = parsables->ambient;
	else
		return (1);
	return (0);
}

// Parses program and fills scene with all its field
int	pars_parseProgram(int fd, t_scene *scene)
{
	t_parsables	parsables;
	char		*line;
	t_cmd_type	cmd_type;

	line = get_next_line(fd);
	while (line)
	{
		pars_parseLine(&parsables, line, &cmdtype);
		//checks if repeated light , cam or ambient
		if (pars_checkCounts(cmdtype, 0))
			return (1);
		pars_fillScene(scene, &parsables, cmdtype);
		line = get_next_line(fd);
	}
	//checks for there are at least 1 object, cam ,light, ambient
	if (pars_checkCounts(0, 1))
		return (1);
	return (0);
}

which depends (among other things ) on the scene interface :

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
}	t_scene;
	
#endif
