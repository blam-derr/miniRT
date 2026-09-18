/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/17 20:35:52 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_bonus.h"
#include "miniRT_bonus.h"
#include "scene_bonus.h"

static char	load_texture(void *mlx, t_mesh *mesh)
{
	t_texture	*texture;
	int			width;
	int			height;

	if (!mesh->material.has_texture)
		return (1);
	texture = &mesh->material.texture;
	texture->img = mlx_xpm_file_to_image(mlx,
			mesh->material.texture_path, &width, &height);
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

void	free_scene_textures(void *mlx, t_scene *scene)
{
	t_list	*node;
	t_mesh	*mesh;

	node = scene->objects;
	while (node)
	{
		mesh = (t_mesh *)node->content;
		if (mesh->material.has_texture && mesh->material.texture.img)
			mlx_destroy_image(mlx, mesh->material.texture.img);
		mesh->material.texture.img = NULL;
		node = node->next;
	}
}
