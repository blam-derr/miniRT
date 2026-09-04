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

uint8_t	parse_sphere(char **values, t_scene *scene)
{
	t_mesh	*sphere;
	t_vec3	vec_color;

	if (string_array_length(values) != 8 || !check_array_of_numbers(values + 1))
		return (0);
	sphere = generate_sphere(32, 16, ft_atof(values[4]));
	if (!sphere)
		return (0);
	sphere->pos.x = ft_atof(values[1]);
	sphere->pos.y = ft_atof(values[2]);
	sphere->pos.z = ft_atof(values[3]);
	sphere->dir = vec3_create(0, 1, 0);
	vec_color.x = ft_atof(values[5]) / 255;
	vec_color.y = ft_atof(values[6]) / 255;
	vec_color.z = ft_atof(values[7]) / 255;
	sphere->material = new_material(vec_color, 0.8, 0.3, 32);
	ft_lstadd_back(&scene->objects, ft_lstnew(sphere));
	return (1);
}

uint8_t	parse_plane(char **values, t_scene *scene)
{
	t_mesh	*plane;
	t_vec3	vec_color;

	if (string_array_length(values) != 10
		|| !check_array_of_numbers(values + 1))
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
	vec_color.x = ft_atof(values[7]) / 255;
	vec_color.y = ft_atof(values[8]) / 255;
	vec_color.z = ft_atof(values[9]) / 255;
	plane->material = new_material(vec_color, 0.8, 0.3, 32);
	ft_lstadd_back(&scene->objects, ft_lstnew(plane));
	return (1);
}

uint8_t	parse_cylinder(char **values, t_scene *scene)
{
	t_mesh	*cylinder;
	t_vec3	vec_color;

	if (string_array_length(values) != 12
		|| !check_array_of_numbers(values + 1))
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
	vec_color.x = ft_atof(values[9]) / 255;
	vec_color.y = ft_atof(values[10]) / 255;
	vec_color.z = ft_atof(values[11]) / 255;
	cylinder->material = new_material(vec_color, 0.8, 0.3, 32);
	ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
	return (1);
}

static t_light	*allocate_sec_lights(t_scene *scene, size_t pos)
{
	t_light	*tmp;
	size_t	i;

	if (scene->secondary_lights == NULL)
	{
		scene->secondary_lights = ft_calloc(5, sizeof(t_light));
		scene->secondary_lights_cap = 5;
		scene->secondary_lights_qty = 0;
		return (scene->secondary_lights);
	}
	if (pos >= scene->secondary_lights_cap)
	{
		tmp = calloc(scene->secondary_lights_cap * 2, sizeof(t_light));
		i = 0;
		while (i < scene->secondary_lights_qty)
		{
			tmp[i] = scene->secondary_lights[i];
			i++;
		}
		free(scene->secondary_lights);
		scene->secondary_lights = tmp;
		scene->secondary_lights_cap *= 2;
	}
	return (scene->secondary_lights);
}

uint8_t	parse_secondary_light(char **values, t_scene *scene)
{
	size_t	pos;

	pos = scene->secondary_lights_qty;
	if (scene->secondary_lights_cap <= pos || scene->secondary_lights == NULL)
	{
		if (!allocate_sec_lights(scene, pos))
			return (0);
	}
	if (string_array_length(values) != 8 || !check_array_of_numbers(values + 1))
		return (0);
	scene->secondary_lights[pos].position.x = ft_atof(values[1]);
	scene->secondary_lights[pos].position.y = ft_atof(values[2]);
	scene->secondary_lights[pos].position.z = ft_atof(values[3]);
	scene->secondary_lights[pos].intensity = ft_atof(values[4]);
	scene->secondary_lights[pos].color.x = ft_atof(values[5]) / 255;
	scene->secondary_lights[pos].color.y = ft_atof(values[6]) / 255;
	scene->secondary_lights[pos].color.z = ft_atof(values[7]) / 255;
	scene->secondary_lights_qty++;
	return (1);
}
