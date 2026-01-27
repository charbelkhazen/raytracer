//#include "parser.h"
#include <fcntl.h>
#include "get_next_line.h"
// parse program


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

static int	pars_checkDuplicates(t_cmd_type type)
{
	static int	count_camera = 0;
	static int	count_light = 0;
	static int	count_ambient = 0;

	if (type == CAMERA_CMD)
		count_camera++;
	else if (type == AMBIENT_CMD)
		count_ambient++;
	else if (type == LIGHT_CMD)
		count_light++;

	if (count_light > 1 || count_camera > 1 || count_ambient > 1)
		return (1)
	return (0);
}

void	pars_fillScene(t_scene *scene, t_parsables *parsables, t_cmd_type cmdtype)
{
	if (cmdtype == CAMERA_CMD)
		cam_fillCam(&scene->cam, scene->img, parsables->view);


// Parses program and fills scene with all its field
// Assumes Scene already has a t_img img element already filled!
//Because img is an important part upon which scene's cam element depends but which is not set by parsing
int	pars_parseProgram(int fd, t_scene *scene)
{
	t_parsables	parsables;
	char		*line;
	t_cmd_type	cmd_type;

	line = get_next_line(fd);
	while (line)
	{
		pars_parseLine(line, &parsables, &cmdtype);
		if (pars_checkDuplicates(cmdtype))
			return (1);
		pars_fillScene(scene, parsables, cmdtype);
	}
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
