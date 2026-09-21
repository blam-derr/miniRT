/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:36:56 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/21 13:49:39 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_bonus.h"
#include "utils_bonus.h"
#include <stddef.h>

static char	*extract_xpm_path(char *token)
{
	size_t	len;
	char	*path;

	len = ft_strlen(token);
	if (len < 4 || token[0] != '"' || token[len - 1] != '"')
		return (NULL);
	path = ft_substr(token, 1, len - 2);
	if (!path)
		return (NULL);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

static void	set_map_fields(t_material *material, int is_bump,
		char *path, float scale)
{
	if (is_bump)
	{
		material->bump_path = path;
		material->has_bump = 1;
		material->bump_strength = scale;
	}
	else
	{
		material->texture_path = path;
		material->has_texture = 1;
		material->texture_scale = scale;
	}
}

static int	parse_map_tail(char **values, int idx, t_material *material,
		int is_bump)
{
	char	*path;
	float	scale;
	int		next;

	if (!values[idx + 1])
		return (-1);
	path = extract_xpm_path(values[idx + 1]);
	if (!path)
		return (-1);
	next = idx + 2;
	scale = 1.0f;
	if (values[next] && is_numeric_token(values[next]))
		scale = ft_atof(values[next++]);
	if (values[next] && ft_strcmp(values[next], "tx") != 0
		&& ft_strcmp(values[next], "bm") != 0)
		return (-1);
	set_map_fields(material, is_bump, path, scale);
	return (next);
}

static int	parse_reflectivity(char *value, t_material *material)
{
	float	reflectivity;

	if (!is_numeric_token(value))
		return (0);
	reflectivity = ft_atof(value);
	if (reflectivity < 0.0f || reflectivity > 1.0f)
		return (0);
	material->reflectivity = reflectivity;
	return (1);
}

int	parse_texture_opt(char **values, int len, int prefix_len,
		t_material *material)
{
	int	i;
	int	next;

	i = prefix_len;
	if (i < len && is_numeric_token(values[i]))
		i += parse_reflectivity(values[i], material);
	while (i < len)
	{
		if (ft_strcmp(values[i], "tx") == 0)
			next = parse_map_tail(values, i, material, 0);
		else if (ft_strcmp(values[i], "bm") == 0)
			next = parse_map_tail(values, i, material, 1);
		else
			return (0);
		if (next < 0)
			return (0);
		i = next;
	}
	return (1);
}
