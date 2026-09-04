/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_bake_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:46:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb_bonus.h"
#include "bvh_bonus.h"
#include "mesh_bonus.h"
#include <math.h>

static void	transform_world_bounds(t_mesh *mesh)
{
	t_local_dirs	dirs;

	dirs.right = mesh->basis_right;
	dirs.forward = mesh->basis_forward;
	dirs.up = mesh->basis_up;
	mesh->world_bounds = aabb_transform(mesh->local_bounds, mesh->pos, dirs);
}

void	mesh_bake_transform(t_mesh *mesh)
{
	t_vec3	world_up;
	size_t	i;

	if (vec3_length(mesh->dir) < EPSILON)
		mesh->basis_forward = vec3_create(0, 1, 0);
	else
		mesh->basis_forward = vec3_normalize(mesh->dir);
	if (fabsf(mesh->basis_forward.y) > 0.999f)
		world_up = vec3_create(1, 0, 0);
	else
		world_up = vec3_create(0, 1, 0);
	mesh->basis_right = vec3_normalize(vec3_cross(world_up,
				mesh->basis_forward));
	mesh->basis_up = vec3_cross(mesh->basis_forward, mesh->basis_right);
	mesh->local_bounds = aabb_empty();
	i = 0;
	while (i < mesh->triangle_count)
	{
		aabb_expand_point(&mesh->local_bounds, mesh->triangles[i].v[0]);
		aabb_expand_point(&mesh->local_bounds, mesh->triangles[i].v[1]);
		aabb_expand_point(&mesh->local_bounds, mesh->triangles[i].v[2]);
		i++;
	}
	transform_world_bounds(mesh);
}
