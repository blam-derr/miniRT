/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:25:14 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/01 16:38:01 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "parser.h"
#include "scene.h"
#include "utils.h"

t_program	init_program(void)
{
	t_program	program;
	t_mlx_args	mlx;

	mlx.mlx = mlx_init();
	program.window_width = 1200;
	program.window_height = 800;
	mlx.window = mlx_new_window(mlx.mlx, program.window_width,
			program.window_height, "MINIRT");
	program.img.width = 1200;
	program.img.height = 800;
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
	mlx_destroy_image(program.mlx.mlx, program.img.img);
	mlx_destroy_window(program.mlx.mlx, program.mlx.window);
	mlx_destroy_display(program.mlx.mlx);
	free(program.mlx.mlx);
}

void	fill_mlx_img(t_scene scene, t_program program)
{
	int				screen_x;
	int				screen_y;
	unsigned int	hex_color;
	t_img_data		*img;

	screen_x = 0;
	img = &program.img;
	while (screen_x < img->width)
	{
		screen_y = 0;
		while (screen_y < img->height)
		{
			hex_color = trace_ray(screen_x, screen_y, scene, program);
			put_pixel(img, screen_x, img->height - screen_y, hex_color);
			screen_y++;
		}
		screen_x++;
	}
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
	fill_mlx_img(scene, program);
	mlx_put_image_to_window(program.mlx.mlx, program.mlx.window,
		program.img.img, 0, 0);
	mlx_key_hook(program.mlx.window, handle_keymaps, &program.mlx);
	mlx_loop(program.mlx.mlx);
	clear_program(program);
	free_whole_scene(&scene);
	return (0);
}
