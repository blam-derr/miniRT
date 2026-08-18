/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blas.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "triangle.h"
#include <stdlib.h>

typedef struct s_stack_item
{
	int		node;
	float	t_enter;
}	t_stack_item;

static void	push(t_stack_item *stack, int *sp, int node, float t)
{
	if (*sp >= BVH_STACK_SIZE)
		return ;
	stack[*sp].node = node;
	stack[*sp].t_enter = t;
	(*sp)++;
}

static void	intersect_leaf_tris(t_mesh *mesh, t_bvh *blas, int first,
		int count, t_ray *ray, t_hit *hit)
{
	int			i;
	int			idx;
	t_triangle	tri;
	float		prev;

	i = 0;
	while (i < count)
	{
		idx = blas->prim_indices[first + i];
		tri = mesh->triangles[idx];
		prev = hit->ray_time;
		intersect_triangle(ray->dir, ray->origin, tri, hit);
		if (hit->ray_time < prev && hit->ray_time < ray->tmax)
			ray->tmax = hit->ray_time;
		i++;
	}
}

static int	any_hit_leaf_tris(t_mesh *mesh, t_bvh *blas, int first, int count,
		t_ray *ray)
{
	int	i;
	int	idx;

	i = 0;
	while (i < count)
	{
		idx = blas->prim_indices[first + i];
		if (is_any_triangle_intersected(ray->dir, ray->origin,
				mesh->triangles[idx], ray->tmax))
			return (1);
		i++;
	}
	return (0);
}

void	intersect_blas(t_mesh *mesh, t_ray *ray, t_hit *hit)
{
	t_bvh			*blas;
	t_stack_item	stack[BVH_STACK_SIZE];
	int				sp;
	t_bvh_node		*node;
	float			t_enter;
	int				cur;

	blas = mesh->blas;
	if (!blas || blas->node_count == 0)
		return ;
	sp = 0;
	push(stack, &sp, blas->root, 0.0f);
	while (sp > 0)
	{
		sp--;
		cur = stack[sp].node;
		if (stack[sp].t_enter >= ray->tmax)
			continue ;
		node = &blas->nodes[cur];
		if (node->is_leaf)
			intersect_leaf_tris(mesh, blas, node->first, node->count,
				ray, hit);
		else
		{
			if (node->left >= 0)
			{
				if (ray_aabb_intersect(ray, blas->nodes[node->left].bounds,
						&t_enter))
					push(stack, &sp, node->left, t_enter);
			}
			if (node->right >= 0)
			{
				if (ray_aabb_intersect(ray, blas->nodes[node->right].bounds,
						&t_enter))
					push(stack, &sp, node->right, t_enter);
			}
		}
	}
}

int	any_hit_blas(t_mesh *mesh, t_ray *ray)
{
	t_bvh			*blas;
	t_stack_item	stack[BVH_STACK_SIZE];
	int				sp;
	t_bvh_node		*node;
	float			t_enter;
	int				cur;

	blas = mesh->blas;
	if (!blas || blas->node_count == 0)
		return (0);
	sp = 0;
	push(stack, &sp, blas->root, 0.0f);
	while (sp > 0)
	{
		sp--;
		cur = stack[sp].node;
		if (stack[sp].t_enter >= ray->tmax)
			continue ;
		node = &blas->nodes[cur];
		if (node->is_leaf)
		{
			if (any_hit_leaf_tris(mesh, blas, node->first, node->count, ray))
				return (1);
		}
		else
		{
			if (node->left >= 0)
			{
				if (ray_aabb_intersect(ray, blas->nodes[node->left].bounds,
						&t_enter))
					push(stack, &sp, node->left, t_enter);
			}
			if (node->right >= 0)
			{
				if (ray_aabb_intersect(ray, blas->nodes[node->right].bounds,
						&t_enter))
					push(stack, &sp, node->right, t_enter);
			}
		}
	}
	return (0);
}

t_bvh	*build_blas(t_mesh *mesh)
{
	t_bvh_prim	*prims;
	t_bvh		*bvh;
	size_t		i;
	t_aabb		box;

	if (!mesh || mesh->triangle_count == 0)
		return (NULL);
	prims = (t_bvh_prim *)malloc(sizeof(t_bvh_prim) * mesh->triangle_count);
	if (!prims)
		return (NULL);
	i = 0;
	while (i < mesh->triangle_count)
	{
		box = aabb_empty();
		aabb_expand_point(&box, mesh->triangles[i].v[0]);
		aabb_expand_point(&box, mesh->triangles[i].v[1]);
		aabb_expand_point(&box, mesh->triangles[i].v[2]);
		prims[i].bounds = box;
		prims[i].centroid = aabb_centroid(box);
		prims[i].index = (int)i;
		i++;
	}
	bvh = bvh_build(prims, (int)mesh->triangle_count);
	free(prims);
	return (bvh);
}
