/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:08:28 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/15 19:41:28 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "scene.h"
#include "parser.h"
#include "utils.h"
#include "vec.h"
#include <stdint.h>

t_dispatched_fn	dispatch(char **values, t_scene *scene)
{
	int							i;
	int							len;
	static t_dict_dispatcher	dict[] = {
	{"A", parse_ambient},
	{"C", parse_camera},
	{"L", parse_light},
	{"sp", parse_ambient},
	{"pl", parse_ambient},
	{"cy", parse_ambient},
	};

	i = 0;
	(void)scene;
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
