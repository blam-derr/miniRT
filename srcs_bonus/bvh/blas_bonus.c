/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blas.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"
#include "triangle_bonus.h"

static void	intersect_leaf_tris(t_mesh *mesh, t_bvh_node *node, t_ray *ray,
		t_hit *hit)
{
	int			i;
	int			idx;
	t_triangle	tri;
	float		prev;

	i = 0;
	while (i < node->count)
	{
		idx = mesh->blas->prim_indices[node->first + i];
		tri = mesh->triangles[idx];
		prev = hit->ray_time;
		intersect_triangle(ray->dir, ray->origin, tri, hit);
		if (hit->ray_time < prev && hit->ray_time < ray->tmax)
			ray->tmax = hit->ray_time;
		i++;
	}
}

static int	any_hit_leaf_tris(t_mesh *mesh, t_bvh_node *node, t_ray *ray)
{
	int	i;
	int	idx;

	i = 0;
	while (i < node->count)
	{
		idx = mesh->blas->prim_indices[node->first + i];
		if (is_any_triangle_intersected(ray->dir, ray->origin,
				mesh->triangles[idx], ray->tmax))
			return (1);
		i++;
	}
	return (0);
}

void	intersect_blas(t_mesh *mesh, t_ray *ray, t_hit *hit)
{
	t_bvh_traversal	tr;
	t_bvh_node		*node;

	if (!mesh->blas || mesh->blas->node_count == 0)
		return ;
	tr.bvh = mesh->blas;
	tr.sp = 0;
	bvh_push(&tr, mesh->blas->root, 0.0f);
	while (tr.sp > 0)
	{
		node = &tr.bvh->nodes[tr.stack[--tr.sp].node];
		if (tr.stack[tr.sp].t_enter >= ray->tmax)
			continue ;
		if (node->is_leaf)
			intersect_leaf_tris(mesh, node, ray, hit);
		else
			bvh_traverse_children(&tr, ray, node);
	}
}

int	any_hit_blas(t_mesh *mesh, t_ray *ray)
{
	t_bvh_traversal	tr;
	t_bvh_node		*node;

	if (!mesh->blas || mesh->blas->node_count == 0)
		return (0);
	tr.bvh = mesh->blas;
	tr.sp = 0;
	bvh_push(&tr, mesh->blas->root, 0.0f);
	while (tr.sp > 0)
	{
		node = &tr.bvh->nodes[tr.stack[--tr.sp].node];
		if (tr.stack[tr.sp].t_enter >= ray->tmax)
			continue ;
		if (node->is_leaf)
		{
			if (any_hit_leaf_tris(mesh, node, ray))
				return (1);
		}
		else
			bvh_traverse_children(&tr, ray, node);
	}
	return (0);
}
