/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlas_any.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

static int	any_hit_instance(t_instance *inst, t_ray *ray, t_mesh *ignore)
{
	t_ray	local;

	if (inst->mesh == ignore)
		return (0);
	local = world_to_local_ray(ray, inst->mesh);
	return (any_hit_blas(inst->mesh, &local));
}

static int	any_hit_leaf_instances(t_accel *accel, t_bvh_node *node,
		t_ray *ray, t_mesh *ignore)
{
	int	i;
	int	idx;

	i = 0;
	while (i < node->count)
	{
		idx = accel->tlas.prim_indices[node->first + i];
		if (any_hit_instance(&accel->instances[idx], ray, ignore))
			return (1);
		i++;
	}
	return (0);
}

int	tlas_any_hit(t_accel *accel, t_ray *ray, t_mesh *ignore_mesh)
{
	t_bvh_traversal	tr;
	t_bvh_node		*node;

	if (!accel || !accel->tlas.nodes)
		return (0);
	tr.bvh = &accel->tlas;
	tr.sp = 0;
	bvh_push(&tr, accel->tlas.root, 0.0f);
	while (tr.sp > 0)
	{
		node = &tr.bvh->nodes[tr.stack[--tr.sp].node];
		if (tr.stack[tr.sp].t_enter >= ray->tmax)
			continue ;
		if (node->is_leaf)
		{
			if (any_hit_leaf_instances(accel, node, ray, ignore_mesh))
				return (1);
		}
		else
			bvh_traverse_children(&tr, ray, node);
	}
	return (0);
}
