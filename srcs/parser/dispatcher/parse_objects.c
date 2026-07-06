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
	// plane->u_data.plane.normal.x = ft_atof(values[4]);
	// plane->u_data.plane.normal.y = ft_atof(values[5]);
	// plane->u_data.plane.normal.z = ft_atof(values[6]);
	vec_color.x = ft_atof(values[7]);
	vec_color.y = ft_atof(values[8]);
	vec_color.z = ft_atof(values[9]);
	plane->base_color = vec_to_hex(vec_color);
	ft_lstadd_back(&scene->objects, ft_lstnew(plane));
	return (1);
}

uint8_t	parse_cylinder(char **values, t_scene *scene)
{
	t_generic_primitive	*cylinder;

	if (string_array_length(values) != 12
		|| !check_array_of_numbers(values + 1))
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
	(void)scene;
	//ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
	return (1);
}
