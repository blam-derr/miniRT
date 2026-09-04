/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:16:51 by jode-cas          #+#    #+#             */
/*   Updated: 2026/09/04 20:45:47 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"
#include "libft.h"
#include "mesh_bonus.h"
#include "scene_bonus.h"
#include <stdlib.h>

static void	destroy_mesh(void *mesh_ptr)
{
	t_mesh	*mesh;

	mesh = (t_mesh *)mesh_ptr;
	free(mesh->triangles);
	free(mesh);
}

void	free_whole_scene(t_scene *scene)
{
	free_scene_accel(scene);
	ft_lstclear(&(scene->objects), destroy_mesh);
}
