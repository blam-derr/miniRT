/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_arrays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "obj_parser.h"
#include <stdlib.h>

static int	grow_array(void **arr, size_t *cap, size_t count, size_t size)
{
	void	*new_arr;
	size_t	new_cap;

	if (count < *cap)
		return (1);
	if (*cap == 0)
		new_cap = 16;
	else
		new_cap = *cap * 2;
	new_arr = malloc(new_cap * size);
	if (!new_arr)
		return (0);
	if (*arr)
	{
		ft_memcpy(new_arr, *arr, count * size);
		free(*arr);
	}
	*arr = new_arr;
	*cap = new_cap;
	return (1);
}

int	push_vec3(t_vec3 **arr, size_t *count, size_t *cap, t_vec3 v)
{
	if (!grow_array((void **)arr, cap, *count, sizeof(t_vec3)))
		return (0);
	(*arr)[*count] = v;
	(*count)++;
	return (1);
}

int	push_triangle(t_obj_data *data, t_triangle tri)
{
	if (!grow_array((void **)&data->tris, &data->t_cap,
			data->t_count, sizeof(t_triangle)))
		return (0);
	data->tris[data->t_count] = tri;
	data->t_count++;
	return (1);
}
