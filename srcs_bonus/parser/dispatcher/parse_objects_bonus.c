/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:44:34 by jode-cas          #+#    #+#             */
/*   Updated: 2026/09/17 15:39:50 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_bonus.h"
#include "scene_bonus.h"
#include "parser_bonus.h"
#include "utils_bonus.h"
#include "vec_bonus.h"
#include <stddef.h>

static t_material	parse_object_material(char **values, int color_idx)
{
	t_material	material;
	t_vec3		color;

	color = vec3_create(ft_atof(values[color_idx]) / 255.0f,
			ft_atof(values[color_idx + 1]) / 255.0f,
			ft_atof(values[color_idx + 2]) / 255.0f);
	material = new_material(color, 0.8, 0.3, 32);
	return (material);
}

uint8_t	check_numeric_range(char **values, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!is_numeric_token(values[i]))
			return (0);
		i++;
	}
	return (1);
}

uint8_t	parse_sphere(char **values, t_scene *scene)
{
	t_mesh		*sphere;
	t_material	material;
	int			len;

	len = string_array_length(values);
	if (len < 8 || len > 12 || !check_numeric_range(values, 1, 8))
		return (0);
	material = parse_object_material(values, 5);
	if (!parse_texture_opt(values, len, 8, &material))
		return (0);
	sphere = generate_sphere(32, 16, ft_atof(values[4]));
	if (!sphere)
		return (0);
	sphere->pos.x = ft_atof(values[1]);
	sphere->pos.y = ft_atof(values[2]);
	sphere->pos.z = ft_atof(values[3]);
	sphere->dir = vec3_create(0, 1, 0);
	sphere->material = material;
	ft_lstadd_back(&scene->objects, ft_lstnew(sphere));
	return (1);
}

uint8_t	parse_plane(char **values, t_scene *scene)
{
	t_mesh		*plane;
	t_material	material;
	int			len;

	len = string_array_length(values);
	if (len < 10 || len > 14 || !check_numeric_range(values, 1, 10))
		return (0);
	material = parse_object_material(values, 7);
	if (!parse_texture_opt(values, len, 10, &material))
		return (0);
	plane = generate_plane();
	if (!plane)
		return (0);
	plane->pos.x = ft_atof(values[1]);
	plane->pos.y = ft_atof(values[2]);
	plane->pos.z = ft_atof(values[3]);
	plane->dir.x = ft_atof(values[4]);
	plane->dir.y = ft_atof(values[5]);
	plane->dir.z = ft_atof(values[6]);
	plane->material = material;
	ft_lstadd_back(&scene->objects, ft_lstnew(plane));
	return (1);
}

uint8_t	parse_cylinder(char **values, t_scene *scene)
{
	t_mesh		*cylinder;
	t_material	material;
	int			len;

	len = string_array_length(values);
	if (len < 12 || len > 16 || !check_numeric_range(values, 1, 12))
		return (0);
	material = parse_object_material(values, 9);
	if (!parse_texture_opt(values, len, 12, &material))
		return (0);
	cylinder = generate_cylinder(32, ft_atof(values[7]), ft_atof(values[8]));
	if (!cylinder)
		return (0);
	cylinder->pos.x = ft_atof(values[1]);
	cylinder->pos.y = ft_atof(values[2]);
	cylinder->pos.z = ft_atof(values[3]);
	cylinder->dir.x = ft_atof(values[4]);
	cylinder->dir.y = ft_atof(values[5]);
	cylinder->dir.z = ft_atof(values[6]);
	cylinder->material = material;
	ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
	return (1);
}
