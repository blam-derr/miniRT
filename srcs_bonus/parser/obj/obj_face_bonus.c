/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_face_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/17 20:38:07 by fbenini-         ###   ########.fr       */
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

static int	parse_uv_index(char *slash1, char *slash2,
		t_obj_data *data, long *uv_idx)
{
	char	*uv_str;
	size_t	len;

	if (slash2 && slash2 == slash1 + 1)
		return (1);
	len = ft_strlen(slash1 + 1);
	if (slash2)
		len = (size_t)(slash2 - slash1 - 1);
	uv_str = ft_substr(slash1 + 1, 0, len);
	if (!uv_str)
		return (0);
	if (!resolve_index(ft_atoi(uv_str), data->uv_count, uv_idx))
	{
		free(uv_str);
		return (0);
	}
	free(uv_str);
	return (1);
}

int	parse_face_token(t_face_token_params params)
{
	char	*slash1;
	char	*slash2;
	long	resolved;

	*params.uv_idx = -1;
	*params.n_idx = -1;
	if (!resolve_index(ft_atoi(params.token), params.data->v_count, &resolved))
		return (0);
	*params.v_idx = (size_t)resolved;
	slash1 = ft_strchr(params.token, '/');
	if (!slash1)
		return (1);
	slash2 = ft_strchr(slash1 + 1, '/');
	if (!parse_uv_index(slash1, slash2, params.data, params.uv_idx))
		return (0);
	if (slash2 && slash2[1] != '\0'
		&& !resolve_index(ft_atoi(slash2 + 1),
			params.data->n_count, params.n_idx))
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

int	emit_triangle(t_obj_data *data, size_t *v, long *n, long *uv)
{
	t_triangle	tri;

	tri.v[0] = data->verts[v[0]];
	tri.v[1] = data->verts[v[1]];
	tri.v[2] = data->verts[v[2]];
	set_tri_normals(data, &tri, n);
	if (uv[0] >= 0 && uv[1] >= 0 && uv[2] >= 0)
	{
		tri.uv[0] = data->uvs[uv[0]];
		tri.uv[1] = data->uvs[uv[1]];
		tri.uv[2] = data->uvs[uv[2]];
		tri.has_uv = 1;
	}
	else
		tri.has_uv = 0;
	return (push_triangle(data, tri));
}
