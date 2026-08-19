/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlas_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "libft.h"
#include "scene.h"
#include <stdlib.h>

static int	count_objects(t_list *objs)
{
	int	n;

	n = 0;
	while (objs)
	{
		n++;
		objs = objs->next;
	}
	return (n);
}

static t_accel	*allocate_accel(int n)
{
	t_accel	*accel;

	accel = (t_accel *)malloc(sizeof(t_accel));
	if (!accel)
		return (NULL);
	accel->instances = (t_instance *)malloc(sizeof(t_instance) * (size_t)n);
	if (!accel->instances)
	{
		free(accel);
		return (NULL);
	}
	accel->instance_count = n;
	accel->tlas.nodes = NULL;
	accel->tlas.prim_indices = NULL;
	accel->tlas.node_count = 0;
	accel->tlas.prim_count = 0;
	accel->tlas.root = 0;
	return (accel);
}

static int	fill_instances(t_accel *accel, t_scene *scene)
{
	t_list	*objs;
	t_mesh	*mesh;
	int		i;

	objs = scene->objects;
	i = 0;
	while (objs)
	{
		mesh = (t_mesh *)objs->content;
		mesh_bake_transform(mesh);
		mesh->blas = build_blas(mesh);
		if (!mesh->blas)
			return (0);
		accel->instances[i].mesh = mesh;
		accel->instances[i].world_bounds = mesh->world_bounds;
		i++;
		objs = objs->next;
	}
	return (1);
}

static int	build_tlas_tree(t_accel *accel)
{
	t_bvh_prim	*prims;
	t_bvh		*built;
	int			i;

	prims = (t_bvh_prim *)malloc(sizeof(t_bvh_prim)
			* (size_t)accel->instance_count);
	if (!prims)
		return (0);
	i = 0;
	while (i < accel->instance_count)
	{
		prims[i].bounds = accel->instances[i].world_bounds;
		prims[i].centroid = aabb_centroid(prims[i].bounds);
		prims[i].index = i;
		i++;
	}
	built = bvh_build(prims, accel->instance_count);
	free(prims);
	if (!built)
		return (0);
	accel->tlas = *built;
	free(built);
	return (1);
}

int	build_scene_accel(t_scene *scene)
{
	t_accel	*accel;
	int		n;

	n = count_objects(scene->objects);
	if (n <= 0)
	{
		scene->accel = NULL;
		return (1);
	}
	accel = allocate_accel(n);
	if (!accel)
		return (0);
	if (!fill_instances(accel, scene) || !build_tlas_tree(accel))
	{
		scene->accel = accel;
		free_scene_accel(scene);
		return (0);
	}
	scene->accel = accel;
	return (1);
}
