/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:27:03 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/14 18:10:15 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

char	**ft_split_charset(char *str, char *charset);
void	free_string_array(char **array);
int		string_array_length(char **array);

double	ft_atof(const char *str);

uint8_t	is_string_whitespace(char *line);

#endif
