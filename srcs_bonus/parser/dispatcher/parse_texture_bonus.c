/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:36:56 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/17 15:43:28 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_bonus.h"
#include "utils_bonus.h"
#include <stddef.h>

int	is_numeric_token(char *s)
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

static int	parse_texture_tail(char **values, int idx, int len,
		t_material *material)
{
	char	*path;
	int		next;

	next = idx + 2;
	if (next < len)
	{
		if (!is_numeric_token(values[next]))
			return (0);
		next++;
	}
	if (next != len)
		return (0);
	path = extract_xpm_path(values[idx + 1]);
	if (!path)
		return (0);
	material->texture_path = path;
	material->has_texture = 1;
	material->texture_scale = 1.0f;
	if (idx + 2 < len)
		material->texture_scale = ft_atof(values[idx + 2]);
	return (1);
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
	if (len == prefix_len)
		return (1);
	if (len == prefix_len + 1)
		return (parse_reflectivity(values[prefix_len], material));
	if (ft_strcmp(values[prefix_len], "tx") == 0)
		return (parse_texture_tail(values, prefix_len, len, material));
	if (!parse_reflectivity(values[prefix_len], material))
		return (0);
	if (len == prefix_len + 2)
		return (1);
	if (ft_strcmp(values[prefix_len + 1], "tx") != 0)
		return (0);
	return (parse_texture_tail(values, prefix_len + 1, len, material));
}
