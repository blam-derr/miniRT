/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:46:07 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/14 16:47:12 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>

static uint8_t	is_file_extension_rt(char *filename)
{
	char	*ext;

	ext = filename + ft_strlen(filename) - 3;
	if (ft_strncmp(ext, ".rt\0", 4) == 0)
		return (1);
	else
	{
		ft_putstr_fd("Error.\n", 2);
		return (0);
	}
}

uint8_t	validate_file(char *filename, int *fd)
{
	if (!is_file_extension_rt(filename))
		return (0);
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd("Error.\n", 2);
		return (0);
	}
	return (1);
}
