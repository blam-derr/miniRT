/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_required.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:19:53 by jode-cas          #+#    #+#             */
/*   Updated: 2026/04/27 17:10:06 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "parser.h"
#include "utils.h"

uint8_t	parse_ambient(char **values, t_scene *scene)
{
	if (string_array_length(values) != 5 || !check_array_of_numbers(values + 1))
		return (0);
	scene->ambient.intensity = ft_atof(values[1]);
	scene->ambient.color.x = ft_atof(values[2]);
	scene->ambient.color.y = ft_atof(values[3]);
	scene->ambient.color.z = ft_atof(values[4]);
	return (1);
}

uint8_t	parse_camera(char **values, t_scene *scene)
{
	if (string_array_length(values) != 8 || !check_array_of_numbers(values + 1))
		return (0);
	scene->camera.position.x = ft_atof(values[1]);
	scene->camera.position.y = ft_atof(values[2]);
	scene->camera.position.z = ft_atof(values[3]);
	scene->camera.direction.x = ft_atof(values[4]);
	scene->camera.direction.y = ft_atof(values[5]);
	scene->camera.direction.z = ft_atof(values[6]);
	scene->camera.fov = ft_atof(values[7]);
	calc_local_cam_axis(&scene->camera);
	return (1);
}

uint8_t	parse_light(char **values, t_scene *scene)
{
	if (string_array_length(values) != 8 || !check_array_of_numbers(values + 1))
		return (0);
	scene->light.position.x = ft_atof(values[1]);
	scene->light.position.y = ft_atof(values[2]);
	scene->light.position.z = ft_atof(values[3]);
	scene->light.intensity = ft_atof(values[4]);
	scene->light.color.x = ft_atof(values[5]);
	scene->light.color.y = ft_atof(values[6]);
	scene->light.color.z = ft_atof(values[7]);
	return (1);
}
