/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:16:51 by jode-cas          #+#    #+#             */
/*   Updated: 2026/04/16 19:23:07 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh.h"
#include "scene.h"
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
	ft_lstclear(&(scene->objects), destroy_mesh);
}
