#include <parser.h>
#include <fcntl.h>
#include <stdint.h>
#include "libft.h"
#include "miniRT.h"
#include "scene.h"
#include "utils.h"

uint8_t	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && !(line[i] >= '\t' && line[i] <= '\r'))
			return (0);
		i++;
	}
	return (1);
}

void	parse_line(char *line, t_scene *scene)
{
	char	**splitted;

	(void)scene;
	if (is_line_empty(line))
		return ;
	splitted = ft_split_charset(line, " \t\n\v\f\r,");
	free_string_array(splitted);
}

t_scene	parse_scene(char *filename)
{
	int		fd;
	char	*line;
	t_scene	scene;

	if (!validate_file(filename, &fd))
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, &scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (scene);
}
