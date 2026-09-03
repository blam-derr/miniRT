/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "obj_parser_bonus.h"
#include "parser_bonus.h"
#include "scene_bonus.h"
#include "utils_bonus.h"
#include <stdlib.h>

static char	*extract_obj_path(char *token)
{
	size_t	len;
	char	*path;

	len = ft_strlen(token);
	if (len < 3 || token[0] != '"' || token[len - 1] != '"')
		return (NULL);
	path = ft_substr(token, 1, len - 2);
	if (!path)
		return (NULL);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".obj", 4) != 0)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

static void	apply_scale(t_mesh *mesh, float scale)
{
	size_t	i;
	int		j;

	i = 0;
	while (i < mesh->triangle_count)
	{
		j = 0;
		while (j < 3)
		{
			mesh->triangles[i].v[j] = vec3_mul(mesh->triangles[i].v[j], scale);
			j++;
		}
		i++;
	}
}

static void	set_obj_props(t_mesh *mesh, char **values, int len)
{
	t_vec3	color;
	float	scale;

	if (len == 12)
	{
		mesh->pos = vec3_create(ft_atof(values[2]), ft_atof(values[3]),
				ft_atof(values[4]));
		mesh->dir = vec3_create(ft_atof(values[5]), ft_atof(values[6]),
				ft_atof(values[7]));
		scale = ft_atof(values[8]);
		color = vec3_create(ft_atof(values[9]) / 255,
				ft_atof(values[10]) / 255, ft_atof(values[11]) / 255);
	}
	else
	{
		mesh->pos = vec3_create(0, 0, 0);
		mesh->dir = vec3_create(0, 1, 0);
		scale = 1.0f;
		color = vec3_create(1, 1, 1);
	}
	mesh->material = new_material(color, 0.8, 0.3, 32);
	apply_scale(mesh, scale);
}

uint8_t	parse_obj(char **values, t_scene *scene)
{
	t_mesh	*mesh;
	char	*path;
	int		len;

	len = string_array_length(values);
	if ((len != 2 && len != 12)
		|| (len == 12 && !check_array_of_numbers(values + 2)))
		return (0);
	if (len == 12 && ft_atof(values[8]) == 0.0)
		return (0);
	path = extract_obj_path(values[1]);
	if (!path)
		return (0);
	mesh = parse_obj_file(path);
	free(path);
	if (!mesh)
		return (0);
	set_obj_props(mesh, values, len);
	ft_lstadd_back(&scene->objects, ft_lstnew(mesh));
	return (1);
}
