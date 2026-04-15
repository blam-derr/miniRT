/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_required.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:19:53 by jode-cas          #+#    #+#             */
/*   Updated: 2026/04/15 19:22:46 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

uint8_t	parse_ambient(char **values, t_scene *scene)
{
	t_vec	color;

	if (string_array_length(values) != 5)
		return (0);
	scene->ambient.intensity = ft_atof(values[1]);
	color.x = ft_atof(values[2]);
	color.y = ft_atof(values[3]);
	color.z = ft_atof(values[4]);
	scene->ambient.color = color;
	return (1);
}

uint8_t	parse_camera(char **values, t_scene *scene)
{
	if (string_array_length(values) != 8)
		return (0);
}

uint8_t	parse_light(char **values, t_scene *scene)
{
	if (string_array_length(values) != 8)
		return (0);
}
