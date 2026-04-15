/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:25:14 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/15 19:05:38 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "parser.h"

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

int	main(int argc, char *argv[])
{
	t_program	program;

	if (argc != 2)
		return (1);
	parse_scene(argv[1]);
	program = init_program();
	mlx_hook(program.mlx.window, 17, 0, close_window, &program.mlx);
	mlx_key_hook(program.mlx.window, handle_keymaps, &program.mlx);
	mlx_loop(program.mlx.mlx);
	clear_program(program);
	return (0);
}
