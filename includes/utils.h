/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:27:03 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/16 18:56:39 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

char	**ft_split_charset(char *str, char *charset);
void	free_string_array(char **array);
int		string_array_length(char **array);
uint8_t	check_array_of_numbers(char **values);

double	ft_atof(const char *str);

uint8_t	is_string_whitespace(char *line);

#endif
