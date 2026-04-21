/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:44:34 by jode-cas          #+#    #+#             */
/*   Updated: 2026/04/16 18:57:52 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "utils.h"

uint8_t	parse_sphere(char **values, t_scene *scene)
{
	t_generic_primitive	*sphere;

	if (string_array_length(values) != 8 || !check_array_of_numbers(values + 1))
		return (0);
	sphere = malloc(sizeof(t_generic_primitive));
	if (!sphere)
		return (0);
	sphere->type = SPHERE;
	sphere->u_data.sphere.position.x = ft_atof(values[1]);
	sphere->u_data.sphere.position.y = ft_atof(values[2]);
	sphere->u_data.sphere.position.z = ft_atof(values[3]);
	sphere->u_data.sphere.radius = ft_atof(values[4]);
	sphere->u_data.sphere.color.x = ft_atof(values[5]);
	sphere->u_data.sphere.color.y = ft_atof(values[6]);
	sphere->u_data.sphere.color.z = ft_atof(values[7]);
	ft_lstadd_back(&scene->objects, ft_lstnew(sphere));
	return (1);
}

uint8_t	parse_plane(char **values, t_scene *scene)
{
	t_generic_primitive	*plane;

	if (string_array_length(values) != 10 || !check_array_of_numbers(values + 1))
		return (0);
	plane = malloc(sizeof(t_generic_primitive));
	if (!plane)
		return (0);
	plane->type = PLANE;
	plane->u_data.plane.position.x = ft_atof(values[1]);
	plane->u_data.plane.position.y = ft_atof(values[2]);
	plane->u_data.plane.position.z = ft_atof(values[3]);
	plane->u_data.plane.normal.x = ft_atof(values[4]);
	plane->u_data.plane.normal.y = ft_atof(values[5]);
	plane->u_data.plane.normal.z = ft_atof(values[6]);
	plane->u_data.plane.color.x = ft_atof(values[7]);
	plane->u_data.plane.color.y = ft_atof(values[8]);
	plane->u_data.plane.color.z = ft_atof(values[9]);
	ft_lstadd_back(&scene->objects, ft_lstnew(plane));
	return (1);
}

uint8_t	parse_cylinder(char **values, t_scene *scene)
{
	t_generic_primitive	*cylinder;

	if (string_array_length(values) != 12 || !check_array_of_numbers(values + 1))
		return (0);
	cylinder = malloc(sizeof(t_generic_primitive));
	if (!cylinder)
		return (0);
	cylinder->type = CYLINDER;
	cylinder->u_data.cylinder.position.x = ft_atof(values[1]);
	cylinder->u_data.cylinder.position.y = ft_atof(values[2]);
	cylinder->u_data.cylinder.position.z = ft_atof(values[3]);
	cylinder->u_data.cylinder.orientation.x = ft_atof(values[4]);
	cylinder->u_data.cylinder.orientation.y = ft_atof(values[5]);
	cylinder->u_data.cylinder.orientation.z = ft_atof(values[6]);
	cylinder->u_data.cylinder.radius = ft_atof(values[7]);
	cylinder->u_data.cylinder.height = ft_atof(values[8]);
	cylinder->u_data.cylinder.color.x = ft_atof(values[9]);
	cylinder->u_data.cylinder.color.y = ft_atof(values[10]);
	cylinder->u_data.cylinder.color.z = ft_atof(values[11]);
	ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
	return (1);
}
