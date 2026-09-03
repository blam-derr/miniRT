/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlas_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"
#include "libft.h"
#include "scene_bonus.h"
#include <stdlib.h>

void	free_scene_accel(t_scene *scene)
{
	t_list	*objs;
	t_mesh	*mesh;

	if (!scene)
		return ;
	objs = scene->objects;
	while (objs)
	{
		mesh = (t_mesh *)objs->content;
		if (mesh && mesh->blas)
		{
			bvh_free(mesh->blas);
			mesh->blas = NULL;
		}
		objs = objs->next;
	}
	if (!scene->accel)
		return ;
	free(scene->accel->tlas.nodes);
	free(scene->accel->tlas.prim_indices);
	free(scene->accel->instances);
	free(scene->accel);
	scene->accel = NULL;
}
