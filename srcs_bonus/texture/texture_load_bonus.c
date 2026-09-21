/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/21 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_bonus.h"
#include "miniRT_bonus.h"
#include "scene_bonus.h"

static char	load_one_texture(void *mlx, t_texture *texture, char *path)
{
	int	width;
	int	height;

	texture->img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!texture->img)
	{
		ft_putstr_fd("Error: cannot load texture.\n", 2);
		return (0);
	}
	texture->width = width;
	texture->height = height;
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	return (1);
}

static char	load_texture(void *mlx, t_mesh *mesh)
{
	if (mesh->material.has_texture
		&& !load_one_texture(mlx, &mesh->material.texture,
			mesh->material.texture_path))
		return (0);
	if (mesh->material.has_bump
		&& !load_one_texture(mlx, &mesh->material.bump,
			mesh->material.bump_path))
		return (0);
	return (1);
}

char	load_scene_textures(void *mlx, t_scene *scene)
{
	t_list	*node;

	node = scene->objects;
	while (node)
	{
		if (!load_texture(mlx, (t_mesh *)node->content))
			return (0);
		node = node->next;
	}
	return (1);
}

static void	destroy_texture(void *mlx, t_texture *texture)
{
	if (texture->img)
		mlx_destroy_image(mlx, texture->img);
	texture->img = NULL;
}

void	free_scene_textures(void *mlx, t_scene *scene)
{
	t_list	*node;
	t_mesh	*mesh;

	node = scene->objects;
	while (node)
	{
		mesh = (t_mesh *)node->content;
		if (mesh->material.has_texture)
			destroy_texture(mlx, &mesh->material.texture);
		if (mesh->material.has_bump)
			destroy_texture(mlx, &mesh->material.bump);
		node = node->next;
	}
}
