/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <stdlib.h>

typedef struct s_build_ctx
{
	t_bvh_prim	*prims;
	t_bvh_node	*nodes;
	int			node_count;
	int			node_cap;
}	t_build_ctx;

static float	centroid_axis(t_vec3 c, int axis)
{
	if (axis == 0)
		return (c.x);
	if (axis == 1)
		return (c.y);
	return (c.z);
}

static void	swap_prim(t_bvh_prim *a, t_bvh_prim *b)
{
	t_bvh_prim	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static t_aabb	bounds_of_range(t_bvh_prim *prims, int first, int count)
{
	t_aabb	box;
	int		i;

	box = aabb_empty();
	i = 0;
	while (i < count)
	{
		aabb_expand_aabb(&box, prims[first + i].bounds);
		i++;
	}
	return (box);
}

static t_aabb	centroid_bounds(t_bvh_prim *prims, int first, int count)
{
	t_aabb	box;
	int		i;

	box = aabb_empty();
	i = 0;
	while (i < count)
	{
		aabb_expand_point(&box, prims[first + i].centroid);
		i++;
	}
	return (box);
}

static int	partition_mid(t_bvh_prim *prims, int first, int count, int axis)
{
	float	mid;
	t_aabb	cb;
	int		i;
	int		j;

	cb = centroid_bounds(prims, first, count);
	if (axis == 0)
		mid = 0.5f * (cb.min.x + cb.max.x);
	else if (axis == 1)
		mid = 0.5f * (cb.min.y + cb.max.y);
	else
		mid = 0.5f * (cb.min.z + cb.max.z);
	i = first;
	j = first + count - 1;
	while (i <= j)
	{
		if (centroid_axis(prims[i].centroid, axis) < mid)
			i++;
		else
		{
			swap_prim(&prims[i], &prims[j]);
			j--;
		}
	}
	return (i - first);
}

static int	new_node(t_build_ctx *ctx)
{
	if (ctx->node_count >= ctx->node_cap)
		return (-1);
	return (ctx->node_count++);
}

static int	build_recursive(t_build_ctx *ctx, int first, int count)
{
	int			node_i;
	int			left_count;
	int			axis;
	t_bvh_node	*node;

	node_i = new_node(ctx);
	if (node_i < 0)
		return (-1);
	node = &ctx->nodes[node_i];
	node->bounds = bounds_of_range(ctx->prims, first, count);
	node->first = first;
	node->count = count;
	node->left = -1;
	node->right = -1;
	if (count <= BVH_LEAF_MAX)
	{
		node->is_leaf = 1;
		return (node_i);
	}
	node->is_leaf = 0;
	axis = aabb_longest_axis(centroid_bounds(ctx->prims, first, count));
	left_count = partition_mid(ctx->prims, first, count, axis);
	if (left_count <= 0 || left_count >= count)
		left_count = count / 2;
	node->left = build_recursive(ctx, first, left_count);
	node->right = build_recursive(ctx, first + left_count,
			count - left_count);
	if (node->left < 0 || node->right < 0)
		return (-1);
	return (node_i);
}

t_bvh	*bvh_build(t_bvh_prim *prims, int prim_count)
{
	t_bvh		*bvh;
	t_build_ctx	ctx;
	int			cap;
	int			i;

	if (prim_count <= 0)
		return (NULL);
	bvh = (t_bvh *)malloc(sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->prim_indices = (int *)malloc(sizeof(int) * (size_t)prim_count);
	if (!bvh->prim_indices)
	{
		free(bvh);
		return (NULL);
	}
	cap = prim_count * 2;
	bvh->nodes = (t_bvh_node *)malloc(sizeof(t_bvh_node) * (size_t)cap);
	if (!bvh->nodes)
	{
		free(bvh->prim_indices);
		free(bvh);
		return (NULL);
	}
	ctx.prims = prims;
	ctx.nodes = bvh->nodes;
	ctx.node_count = 0;
	ctx.node_cap = cap;
	bvh->root = build_recursive(&ctx, 0, prim_count);
	if (bvh->root < 0)
	{
		free(bvh->nodes);
		free(bvh->prim_indices);
		free(bvh);
		return (NULL);
	}
	bvh->node_count = ctx.node_count;
	bvh->prim_count = prim_count;
	i = 0;
	while (i < prim_count)
	{
		bvh->prim_indices[i] = prims[i].index;
		i++;
	}
	return (bvh);
}

void	bvh_free(t_bvh *bvh)
{
	if (!bvh)
		return ;
	free(bvh->nodes);
	free(bvh->prim_indices);
	free(bvh);
}
