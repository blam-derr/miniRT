/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:32:15 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:49:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include "scene_bonus.h"
# include <stdint.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

t_scene				parse_scene(char *filename);
uint8_t				parse_ambient(char **values, t_scene *scene);
uint8_t				parse_camera(char **values, t_scene *scene);
uint8_t				parse_light(char **values, t_scene *scene);
uint8_t				parse_secondary_light(char **values, t_scene *scene);
uint8_t				parse_sphere(char **values, t_scene *scene);
uint8_t				parse_plane(char **values, t_scene *scene);
uint8_t				parse_cylinder(char **values, t_scene *scene);
uint8_t				parse_obj(char **values, t_scene *scene);
uint8_t				validate_file(char *filename, int *fd);

typedef uint8_t		(*t_dispatched_fn)(char **values, t_scene *scene);

typedef struct s_dict_dispatcher
{
	char			*key;
	t_dispatched_fn	function;
}					t_dict_dispatcher;

t_dispatched_fn		dispatch(char **values);

#endif
