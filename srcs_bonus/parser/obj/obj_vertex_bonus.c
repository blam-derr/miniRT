/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_vertex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "obj_parser_bonus.h"
#include "utils_bonus.h"

static int	is_obj_number(char *s)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			has_digit = 1;
		else if (s[i] != '.' && s[i] != 'e' && s[i] != 'E'
			&& s[i] != '-' && s[i] != '+')
			return (0);
		i++;
	}
	return (has_digit);
}

int	parse_vec3_line(char **tokens, t_obj_data *data, int is_normal)
{
	t_vec3	v;

	if (string_array_length(tokens) < 4
		|| !is_obj_number(tokens[1])
		|| !is_obj_number(tokens[2])
		|| !is_obj_number(tokens[3]))
		return (0);
	v.x = ft_atof(tokens[1]);
	v.y = ft_atof(tokens[2]);
	v.z = ft_atof(tokens[3]);
	if (is_normal)
		return (push_vec3(&data->normals, &data->n_count, &data->n_cap, v));
	return (push_vec3(&data->verts, &data->v_count, &data->v_cap, v));
}
