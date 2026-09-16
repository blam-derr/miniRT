/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:08:02 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:45:47 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT_bonus.h"
#include "parser_bonus.h"
#include "scene_bonus.h"
#include "utils_bonus.h"

uint8_t	parse_line(char *line, t_scene *scene)
{
	char			**splitted;
	t_dispatched_fn	fn;
	int				is_ok;

	(void)scene;
	if (is_string_whitespace(line))
		return (1);
	splitted = ft_split_charset(line, " \t\n\v\f\r,");
	fn = dispatch(splitted);
	if (!fn)
	{
		free_string_array(splitted);
		return (0);
	}
	is_ok = fn(splitted, scene);
	free_string_array(splitted);
	return (is_ok);
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
	exit(1);
}

static void	set_initial_scene(t_scene *scene)
{
	scene->objects = NULL;
	scene->accel = NULL;
	scene->secondary_lights = NULL;
	scene->secondary_lights_qty = 0;
	scene->secondary_lights_cap = 0;
	scene->has_ambient = 0;
	scene->has_light = 0;
	scene->has_camera = 0;
}

char	check_scene_requireds(t_scene scene)
{
	if (!scene.has_ambient)
	{
		ft_putstr_fd("Error: No ambient value.\n", 2);
		return (0);
	}
	if (!scene.has_light)
	{
		ft_putstr_fd("Error: No light value.\n", 2);
		return (0);
	}
	if (!scene.has_camera)
	{
		ft_putstr_fd("Error: No camera value.\n", 2);
		return (0);
	}
	return (1);
}

t_scene	parse_scene(char *filename)
{
	int		fd;
	char	*line;
	t_scene	scene;

	set_initial_scene(&scene);
	if (!validate_file(filename, &fd))
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, &scene))
		{
			ft_putstr_fd("Error.\n", 2);
			graceful_exit(line, fd, &scene);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!check_scene_requireds(scene))
		graceful_exit(NULL, fd, &scene);
	return (scene);
}
