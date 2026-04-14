#include <parser.h>
#include <fcntl.h>
#include "libft.h"

void	parse_scene(char *filename)
{
	int	fd;

	if (!validate_file(filename, &fd))
		exit(0);
	close(fd);
}
