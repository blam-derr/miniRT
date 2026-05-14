/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:27:03 by fbenini-          #+#    #+#             */
/*   Updated: 2026/05/12 20:25:40 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "miniRT.h"
# include "vec.h"
# include "scene.h"
# include <stdint.h>

char			**ft_split_charset(char *str, char *charset);
void			free_string_array(char **array);
int				string_array_length(char **array);
uint8_t			check_array_of_numbers(char **values);

double			ft_atof(const char *str);

uint8_t			is_string_whitespace(char *line);

void			put_pixel(t_img_data *data, int x, int y, unsigned int color);
uint32_t		vec_to_hex(t_vec3 color);
t_vec3			apply_color_intensity(float intensity, t_vec3 color);

unsigned int	trace_ray(int x, int y, t_scene scene, t_program program);

#endif
