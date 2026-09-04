/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:08:28 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:46:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include <stdint.h>

t_dispatched_fn	dispatch(char **values)
{
	int							i;
	int							len;
	static t_dict_dispatcher	dict[] = {
	{"A", parse_ambient},
	{"C", parse_camera},
	{"L", parse_light},
	{"l", parse_secondary_light},
	{"sp", parse_sphere},
	{"pl", parse_plane},
	{"cy", parse_cylinder},
	{".obj", parse_obj},
	};

	i = 0;
	if (!values || !values[0])
		return (NULL);
	len = sizeof(dict) / sizeof(t_dict_dispatcher);
	while (i < len)
	{
		if (ft_strcmp(values[0], dict[i].key) == 0)
			return (dict[i].function);
		i++;
	}
	return (NULL);
}
