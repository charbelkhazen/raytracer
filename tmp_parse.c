//#include "parser.h"
#include <fcntl.h>
#include "get_next_line.h"
// parse program

//single elements that you can parse from user
typedef struct s_parsables
{
	t_light light;
	t_amb	amb;
	t_view	view;
	t_obj	obj;
}	t_parsables;

typedef enum
{
	CAMERA_CMD;
	LIGHT_CMD;
	AMBIENT_CMD;
	OBJECT_CMD;
}	t_cmd_type;

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
	else if (type == OBJECT_CMD)
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
	else if (cmdtype == OBJECT_CMD)
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
		if (pars_checkCounts(cmdtype, 0))
			return (1);
		pars_fillScene(scene, &parsables, cmdtype);
		line = get_next_line(fd);
	}
	if (pars_checkCounts(0, 1))
		return (1);
	return (0);
}

#include <stdio.h>
int main()
{
	int fd;

	fd = open("minirt.rt", O_RDONLY);
	char *line;
	while(line = get_next_line(fd))
	{
		printf("%s\n", line);
	}
	close(fd);
}
