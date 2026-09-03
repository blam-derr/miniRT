/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_face_line.c                                    :+:      :+:    :+:   */
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
#include <stdlib.h>

static int	alloc_face_idx(t_face_idx *face)
{
	face->v = malloc(sizeof(size_t) * face->count);
	face->n = malloc(sizeof(long) * face->count);
	if (!face->v || !face->n)
	{
		free(face->v);
		free(face->n);
		return (0);
	}
	return (1);
}

static void	free_face_idx(t_face_idx *face)
{
	free(face->v);
	free(face->n);
}

static int	fill_face_idx(char **tokens, t_obj_data *data, t_face_idx *face)
{
	int	i;

	i = 0;
	while (i < face->count)
	{
		if (!parse_face_token(tokens[i + 1], data, &face->v[i], &face->n[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	fan_triangulate(t_obj_data *data, t_face_idx *face)
{
	int		i;
	size_t	v[3];
	long	n[3];

	i = 1;
	while (i < face->count - 1)
	{
		v[0] = face->v[0];
		v[1] = face->v[i];
		v[2] = face->v[i + 1];
		n[0] = face->n[0];
		n[1] = face->n[i];
		n[2] = face->n[i + 1];
		if (!emit_triangle(data, v, n))
			return (0);
		i++;
	}
	return (1);
}

int	parse_face_line(char **tokens, t_obj_data *data)
{
	t_face_idx	face;
	int			ok;

	face.count = string_array_length(tokens) - 1;
	if (face.count < 3)
		return (0);
	if (!alloc_face_idx(&face))
		return (0);
	ok = fill_face_idx(tokens, data, &face);
	if (ok)
		ok = fan_triangulate(data, &face);
	free_face_idx(&face);
	return (ok);
}
