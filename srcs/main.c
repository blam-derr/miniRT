/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:25:14 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/21 19:26:21 by fbenini-         ###   ########.fr       */
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
	mlx_destroy_image(program.mlx.mlx, program.img.img);
	mlx_destroy_window(program.mlx.mlx, program.mlx.window);
	mlx_destroy_display(program.mlx.mlx);
	free(program.mlx.mlx);
}

void	fill_mlx_img(t_scene scene, t_img_data *img)
{
	int				i;
	int				j;
	t_vec			rgb_color;
	unsigned int	hex_color;
	float			intensity;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		intensity = scene.ambient.intensity;
		while (j < img->height)
		{
			rgb_color = apply_color_intensity(
					intensity, scene.ambient.color);
			hex_color = vec_to_hex(rgb_color);
			put_pixel(img, i, j, hex_color);
			j++;
			intensity -= (float)j / 1e6;
		}
		i++;
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
	fill_mlx_img(scene, &program.img);
	mlx_put_image_to_window(program.mlx.mlx, program.mlx.window,
		program.img.img, 0, 0);
	mlx_key_hook(program.mlx.window, handle_keymaps, &program.mlx);
	mlx_loop(program.mlx.mlx);
	clear_program(program);
	free_whole_scene(&scene);
	return (0);
}
