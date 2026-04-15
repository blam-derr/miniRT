/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:32:15 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/15 12:10:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include <stdint.h>

t_scene			parse_scene(char *filename);

uint8_t			validate_file(char *filename, int *fd);

typedef uint8_t	(*t_dispatched_fn)(char **values, t_scene *scene);

typedef struct s_dict_dispatcher
{
	char			*key;
	t_dispatched_fn	function;
}				t_dict_dispatcher;

t_dispatched_fn	dispatch(char **values, t_scene *scene);

#endif
