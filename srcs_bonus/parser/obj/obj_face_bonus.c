/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_face.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "obj_parser_bonus.h"

static int	resolve_index(int idx, size_t count, long *out)
{
	long	res;

	if (idx > 0)
		res = (long)idx - 1;
	else if (idx < 0)
		res = (long)count + (long)idx;
	else
		return (0);
	if (res < 0 || res >= (long)count)
		return (0);
	*out = res;
	return (1);
}

int	parse_face_token(char *token, t_obj_data *data, size_t *v_idx, long *n_idx)
{
	char	*slash1;
	char	*slash2;
	long	resolved;

	*n_idx = -1;
	if (!resolve_index(ft_atoi(token), data->v_count, &resolved))
		return (0);
	*v_idx = (size_t)resolved;
	slash1 = ft_strchr(token, '/');
	if (!slash1)
		return (1);
	slash2 = ft_strchr(slash1 + 1, '/');
	if (slash2 && slash2[1] != '\0'
		&& !resolve_index(ft_atoi(slash2 + 1), data->n_count, n_idx))
		return (0);
	return (1);
}

void	set_tri_normals(t_obj_data *data, t_triangle *tri, long *n)
{
	t_vec3	geo;

	if (n[0] >= 0 && n[1] >= 0 && n[2] >= 0)
	{
		tri->n[0] = data->normals[n[0]];
		tri->n[1] = data->normals[n[1]];
		tri->n[2] = data->normals[n[2]];
	}
	else
	{
		geo = vec3_normalize(vec3_cross(
					vec3_sub(tri->v[1], tri->v[0]),
					vec3_sub(tri->v[2], tri->v[0])));
		tri->n[0] = geo;
		tri->n[1] = geo;
		tri->n[2] = geo;
	}
}

int	emit_triangle(t_obj_data *data, size_t *v, long *n)
{
	t_triangle	tri;

	tri.v[0] = data->verts[v[0]];
	tri.v[1] = data->verts[v[1]];
	tri.v[2] = data->verts[v[2]];
	set_tri_normals(data, &tri, n);
	return (push_triangle(data, tri));
}
