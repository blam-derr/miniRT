/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:44:34 by jode-cas          #+#    #+#             */
/*   Updated: 2026/04/15 19:47:54 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "utils.h"

uint8_t	parse_sphere(char **values, t_scene *scene)
{
	t_sphere	*sphere;

	if (string_array_length(values) != 6)
		return (0);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->position.x = ft_atof(values[1]);
	sphere->position.y = ft_atof(values[2]);
	sphere->position.z = ft_atof(values[3]);
	sphere->radius = ft_atof(values[4]);
	sphere->color.x = ft_atof(values[5]);
	sphere->color.y = ft_atof(values[6]);
	sphere->color.z = ft_atof(values[7]);
	ft_lstadd_back(&scene->objects, ft_lstnew(sphere));
	return (1);
}

uint8_t	parse_plane(char **values, t_scene *scene)
{
	t_plane	*plane;

	if (string_array_length(values) != 7)
		return (0);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->position.x = ft_atof(values[1]);
	plane->position.y = ft_atof(values[2]);
	plane->position.z = ft_atof(values[3]);
	plane->normal.x = ft_atof(values[4]);
	plane->normal.y = ft_atof(values[5]);
	plane->normal.z = ft_atof(values[6]);
	plane->color.x = ft_atof(values[7]);
	plane->color.y = ft_atof(values[8]);
	plane->color.z = ft_atof(values[9]);
	ft_lstadd_back(&scene->objects, ft_lstnew(plane));
	return (1);
}

uint8_t	parse_cylinder(char **values, t_scene *scene)
{
	t_cylinder	*cylinder;

	if (string_array_length(values) != 9)
		return (0);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->position.x = ft_atof(values[1]);
	cylinder->position.y = ft_atof(values[2]);
	cylinder->position.z = ft_atof(values[3]);
	cylinder->orientation.x = ft_atof(values[4]);
	cylinder->orientation.y = ft_atof(values[5]);
	cylinder->orientation.z = ft_atof(values[6]);
	cylinder->radius = ft_atof(values[7]);
	cylinder->height = ft_atof(values[8]);
	cylinder->color.x = ft_atof(values[9]);
	cylinder->color.y = ft_atof(values[10]);
	cylinder->color.z = ft_atof(values[11]);
	ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
	return (1);
}
