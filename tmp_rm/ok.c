#include "get_next_line.h"
#include <fcntl.h>


int main()
{
	char *line;
	int	fd;

	fd = open("map.rt", O_RDONLY);

	line = get_next_line(fd);
}

