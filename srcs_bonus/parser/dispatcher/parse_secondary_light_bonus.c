/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_secondary_light_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/14 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene_bonus.h"
#include "utils_bonus.h"
#include <stddef.h>
#include <stdlib.h>

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
