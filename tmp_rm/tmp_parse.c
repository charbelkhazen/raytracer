//#include "parser.h"
#include <fcntl.h>
#include "get_next_line.h"
// parse program

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
			return (1);
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
	img_fill(&scene->cam.img, img_width, img_ratio);
}

int	pars_fillScene(t_scene *scene, t_parsables *parsables, t_cmd_type cmdtype)
{
	if (cmdtype == CAMERA_CMD)
	{
		pars_setDefaultImg(scene);
		cam_fillCam(&scene->cam, scene->cam.img, parsables->view);
	}
	else if (cmdtype == SPHERE_CMD) // TODO : DO THE SAME WITH CYL AND PLANE
	{
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

//TODO: REFACTOR IF YOU HAVE TIME responsibabilities are not clear : checking + filling + initialzing init + initializing img - All this in one fnuction
//FUNCTION INITIALIZES UNIV BEFORE STARTING THE PARSING
// Parses program and fills scene with all its field
int	pars_parseProgram(int fd, t_scene *scene)
{
	t_parsables	parsables;
	char		*line;
	t_cmd_type	cmdtype;

	univ_init(&scene.univ);
	line = get_next_line(fd);
	while (line)
	{
		if (pars_parseLine(&parsables, line, &cmdtype))
		{
			free(line);
			return (1);
		}
		//checks if repeated light , cam or ambient
		if (pars_checkCounts(cmdtype, 0))
		{
			free(line);
			return (1);
		}
		if (pars_fillScene(scene, &parsables, cmdtype))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	//checks for there are at least 1 object, cam ,light, ambient
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
