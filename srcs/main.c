/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:25:14 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/16 20:45:36 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "parser.h"
#include "utils.h"

t_program	init_program(void)
{
	t_program	program;
	t_mlx_args	mlx;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 800, 600, "MINIRT");
	program.img.width = 800;
	program.img.height = 600;
	program.img.img = mlx_new_image(mlx.mlx, program.img.width,
			program.img.height);
	program.img.addr = mlx_get_data_addr(program.img.img,
			&program.img.bits_per_pixel, &program.img.line_length,
			&program.img.endian);
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
	t_scene		scene;

	if (argc != 2)
		return (1);
	scene = parse_scene(argv[1]);
	program = init_program();
	mlx_hook(program.mlx.window, 17, 0, close_window, &program.mlx);
	put_pixel(&program.img, 40, 40, 0xFF0000);
	mlx_put_image_to_window(program.mlx.mlx, program.mlx.window,
		program.img.img, 0, 0);
	mlx_key_hook(program.mlx.window, handle_keymaps, &program.mlx);
	mlx_loop(program.mlx.mlx);
	clear_program(program);
	free_whole_scene(&scene);
	return (0);
}
