/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:25:24 by fbenini-          #+#    #+#             */
/*   Updated: 2026/05/12 20:21:49 by fbenini-         ###   ########.fr       */
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

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img_data;

typedef struct s_program
{
	t_mlx_args	mlx;
	t_img_data	img;
	int			window_width;
	int			window_height;
}				t_program;

void			free_int_array(int *array);
int				int_array_length(int *array);
void			free_string_array(char **array);
int				string_array_length(char **array);

#endif
