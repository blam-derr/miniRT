/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:25:18 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/13 17:26:27 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	close_window(void *params)
{
	t_mlx_args	*mlx;

	mlx = (t_mlx_args *)params;
	mlx_loop_end(mlx->mlx);
	ft_printf("👋 Leaving now, bye!\n");
	return (0);
}

int	handle_keymaps(int keycode, void *params)
{
	t_mlx_args	*mlx;

	mlx = (t_mlx_args *)params;
	if (keycode == 65307)
	{
		mlx_loop_end(mlx->mlx);
		ft_printf("👋 Leaving now, bye!\n");
	}
	return (0);
}
