#include "parser.h"
#include <fcntl.h>
#include "get_next_line.h"
#include "scene.h"
int main()
{
	char *line;
	int	fd;
	t_scene	scene;

	fd = open("minirt.rt", O_RDONLY);

	pars_parseProgram(fd, &scene);

	close(fd);
}
