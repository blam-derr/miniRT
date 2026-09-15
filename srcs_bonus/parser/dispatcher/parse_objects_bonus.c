/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:44:34 by jode-cas          #+#    #+#             */
/*   Updated: 2026/09/04 20:46:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_bonus.h"
#include "scene_bonus.h"
#include "utils_bonus.h"
#include "vec_bonus.h"
#include <stddef.h>
#include <stdio.h>

static t_material	parse_object_material(char **values, int len, int color_idx)
{
	t_material	material;
	t_vec3		color;

	color = vec3_create(ft_atof(values[color_idx]) / 255.0f,
			ft_atof(values[color_idx + 1]) / 255.0f,
			ft_atof(values[color_idx + 2]) / 255.0f);
	material = new_material(color, 0.8, 0.3, 32);
	if (len > color_idx + 3)
		material.reflectivity = ft_atof(values[color_idx + 3]);
	if (material.reflectivity < 0.0f || material.reflectivity > 1.0f)
		material.reflectivity = -1.0f;
	return (material);
}

uint8_t	parse_sphere(char **values, t_scene *scene)
{
	t_mesh		*sphere;
	t_material	material;
	int			len;

	len = string_array_length(values);
	if ((len != 8 && len != 9) || !check_array_of_numbers(values + 1))
		return (0);
	material = parse_object_material(values, len, 5);
	if (material.reflectivity < 0.0f)
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
	if ((len != 10 && len != 11) || !check_array_of_numbers(values + 1))
		return (0);
	material = parse_object_material(values, len, 7);
	if (material.reflectivity < 0.0f)
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
	if ((len != 12 && len != 13) || !check_array_of_numbers(values + 1))
		return (0);
	material = parse_object_material(values, len, 9);
	if (material.reflectivity < 0.0f)
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
