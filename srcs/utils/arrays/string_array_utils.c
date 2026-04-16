/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:00:42 by jode-cas          #+#    #+#             */
/*   Updated: 2026/04/16 19:03:56 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdint.h>

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	string_array_length(char **array)
{
	int	length;

	length = 0;
	if (!array)
		return (0);
	while (array[length])
		length++;
	return (length);
}

uint8_t	check_array_of_numbers(char **values)
{
	int	i;
	int	j;

	i = 0;
	while (values[i])
	{
		j = 0;
		if (values[i][j] == '-' || values[i][j] == '+')
		{
			if (!ft_isdigit(values[i][j + 1]))
				return (0);
			j++;
		}
		while (values[i][j])
		{
			if (!ft_isdigit(values[i][j]) && values[i][j] != '.')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
