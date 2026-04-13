/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:00:42 by jode-cas          #+#    #+#             */
/*   Updated: 2026/04/13 18:03:08 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_int_array(int *array)
{
	if (!array)
		return ;
	free(array);
}

int	int_array_length(int *array)
{
	int	length;

	length = 0;
	if (!array)
		return (0);
	while (array[length] != 0)
		length++;
	return (length);
}
