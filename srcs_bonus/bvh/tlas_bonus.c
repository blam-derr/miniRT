/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlas_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:46:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"

t_ray	world_to_local_ray(t_ray *world, t_mesh *mesh)
{
	t_vec3	p;
	t_vec3	local_o;
	t_vec3	local_d;
	t_ray	local;

	p = vec3_sub(world->origin, mesh->pos);
	local_o.x = vec3_dot(p, mesh->basis_right);
	local_o.y = vec3_dot(p, mesh->basis_forward);
	local_o.z = vec3_dot(p, mesh->basis_up);
	local_d.x = vec3_dot(world->dir, mesh->basis_right);
	local_d.y = vec3_dot(world->dir, mesh->basis_forward);
	local_d.z = vec3_dot(world->dir, mesh->basis_up);
	local = ray_make(local_o, local_d, world->tmin, world->tmax);
	return (local);
}

static void	intersect_instance(t_instance *inst, t_ray *ray, t_hit *hit)
{
	t_ray	local;
	float	prev;

	local = world_to_local_ray(ray, inst->mesh);
	prev = hit->ray_time;
	intersect_blas(inst->mesh, &local, hit);
	if (hit->ray_time < prev)
	{
		hit->mesh = inst->mesh;
		hit->basis_right = inst->mesh->basis_right;
		hit->basis_forward = inst->mesh->basis_forward;
		hit->basis_up = inst->mesh->basis_up;
		ray->tmax = hit->ray_time;
	}
}

static void	intersect_leaf_instances(t_accel *accel, t_bvh_node *node,
		t_ray *ray, t_hit *hit)
{
	int	i;
	int	idx;

	i = 0;
	while (i < node->count)
	{
		idx = accel->tlas.prim_indices[node->first + i];
		intersect_instance(&accel->instances[idx], ray, hit);
		i++;
	}
}

void	intersect_tlas(t_accel *accel, t_ray *ray, t_hit *hit)
{
	t_bvh_traversal	tr;
	t_bvh_node		*node;

	if (!accel || !accel->tlas.nodes)
		return ;
	tr.bvh = &accel->tlas;
	tr.sp = 0;
	bvh_push(&tr, accel->tlas.root, 0.0f);
	while (tr.sp > 0)
	{
		node = &tr.bvh->nodes[tr.stack[--tr.sp].node];
		if (tr.stack[tr.sp].t_enter >= ray->tmax)
			continue ;
		if (node->is_leaf)
			intersect_leaf_instances(accel, node, ray, hit);
		else
			bvh_traverse_children(&tr, ray, node);
	}
}
