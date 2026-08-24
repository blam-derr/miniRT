/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "obj_parser.h"
#include "utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	init_obj_data(t_obj_data *data)
{
	data->verts = NULL;
	data->v_count = 0;
	data->v_cap = 0;
	data->normals = NULL;
	data->n_count = 0;
	data->n_cap = 0;
	data->tris = NULL;
	data->t_count = 0;
	data->t_cap = 0;
}

static void	free_obj_data(t_obj_data *data)
{
	free(data->verts);
	free(data->normals);
	free(data->tris);
}

static int	process_line(char *line, t_obj_data *data)
{
	char	**tokens;
	int		ok;

	if (is_string_whitespace(line))
		return (1);
	tokens = ft_split_charset(line, " \t\n\v\f\r");
	if (!tokens)
		return (0);
	if (!tokens[0])
	{
		free_string_array(tokens);
		return (1);
	}
	ok = 1;
	if (ft_strcmp(tokens[0], "v") == 0)
		ok = parse_vec3_line(tokens, data, 0);
	else if (ft_strcmp(tokens[0], "vn") == 0)
		ok = parse_vec3_line(tokens, data, 1);
	else if (ft_strcmp(tokens[0], "f") == 0)
		ok = parse_face_line(tokens, data);
	free_string_array(tokens);
	return (ok);
}

static t_mesh	*assemble_mesh(t_obj_data *data)
{
	t_mesh	*mesh;

	if (data->t_count == 0)
	{
		free_obj_data(data);
		return (NULL);
	}
	mesh = malloc(sizeof(t_mesh));
	if (!mesh)
	{
		free_obj_data(data);
		return (NULL);
	}
	mesh->triangle_count = data->t_count;
	mesh->triangles = data->tris;
	mesh->blas = NULL;
	free(data->verts);
	free(data->normals);
	return (mesh);
}

t_mesh	*parse_obj_file(char *filename)
{
	int			fd;
	char		*line;
	t_obj_data	data;
	int			ok;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	init_obj_data(&data);
	ok = 1;
	line = get_next_line(fd);
	while (line && ok)
	{
		ok = process_line(line, &data);
		free(line);
		if (ok)
			line = get_next_line(fd);
	}
	close(fd);
	if (!ok)
	{
		free_obj_data(&data);
		return (NULL);
	}
	return (assemble_mesh(&data));
}
