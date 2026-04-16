/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:08:02 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/16 19:23:07 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parser.h"
#include "scene.h"
#include "utils.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

uint8_t	parse_line(char *line, t_scene *scene)
{
	char			**splitted;
	t_dispatched_fn	fn;
	int				res;

	(void)scene;
	if (is_string_whitespace(line))
		return (1);
	splitted = ft_split_charset(line, " \t\n\v\f\r,");
	fn = dispatch(splitted, scene);
	if (!fn)
	{
		free_string_array(splitted);
		return (0);
	}
	res = fn(splitted, scene);
	free_string_array(splitted);
	return (res);
}

void	graceful_exit(char *line, int fd, t_scene *scene)
{
	free_whole_scene(scene);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_putstr_fd("Error.\n", 2);
	exit(1);
}

t_scene	parse_scene(char *filename)
{
	int		fd;
	char	*line;
	t_scene	scene;

	if (!validate_file(filename, &fd))
		exit(1);
	line = get_next_line(fd);
	scene.objects = NULL;
	while (line)
	{
		if (!parse_line(line, &scene))
			graceful_exit(line, fd, &scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (scene);
}
