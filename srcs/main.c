/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:25:14 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/13 17:26:53 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"

t_program	init_program(void)
{
	t_program	program;
	t_mlx_args	mlx;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 800, 600, "MINIRT");
	program.mlx = mlx;
	return (program);
}

void	clear_program(t_program program)
{
	mlx_destroy_window(program.mlx.mlx, program.mlx.window);
	mlx_destroy_display(program.mlx.mlx);
	free(program.mlx.mlx);
}

int	main(void)
{
	t_program	program;

	program = init_program();
	mlx_hook(program.mlx.window, 17, 0, close_window, &program.mlx);
	mlx_key_hook(program.mlx.window, handle_keymaps, &program.mlx);
	mlx_loop(program.mlx.mlx);
	clear_program(program);
	return (0);
}
