/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:25:24 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/13 18:05:34 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "hooks.h"
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>

typedef struct s_mlx_args
{
	void		*mlx;
	void		*window;
}				t_mlx_args;

typedef struct s_program
{
	t_mlx_args	mlx;
}				t_program;

void			free_int_array(int *array);
int				int_array_length(int *array);
void			free_string_array(char **array);
int				string_array_length(char **array);

#endif
