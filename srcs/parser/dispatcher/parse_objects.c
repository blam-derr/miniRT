/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:44:34 by jode-cas          #+#    #+#             */
/*   Updated: 2026/07/06 19:59:30 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "scene.h"
#include "utils.h"
#include "vec.h"

uint8_t	parse_sphere(char **values, t_scene *scene)
{
	t_mesh	*sphere;
	t_vec3	vec_color;

	if (string_array_length(values) != 8 || !check_array_of_numbers(values + 1))
		return (0);
	sphere = generate_sphere(20, 10, ft_atof(values[4]));
	if (!sphere)
		return (0);
	sphere->pos.x = ft_atof(values[1]);
	sphere->pos.y = ft_atof(values[2]);
	sphere->pos.z = ft_atof(values[3]);
	sphere->dir = vec3_create(0, 1, 0);
	vec_color.x = ft_atof(values[5]);
	vec_color.y = ft_atof(values[6]);
	vec_color.z = ft_atof(values[7]);
	sphere->base_color = vec_to_hex(vec_color);
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
	vec_color.x = ft_atof(values[7]);
	vec_color.y = ft_atof(values[8]);
	vec_color.z = ft_atof(values[9]);
	plane->base_color = vec_to_hex(vec_color);
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
	vec_color.x = ft_atof(values[9]);
	vec_color.y = ft_atof(values[10]);
	vec_color.z = ft_atof(values[11]);
	cylinder->base_color = vec_to_hex(vec_color);
	ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
	return (1);
}
