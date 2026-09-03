/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"

static int	init_node(t_build_ctx *ctx, int first, int count)
{
	int			node_i;
	t_bvh_node	*node;

	if (ctx->node_count >= ctx->node_cap)
		return (-1);
	node_i = ctx->node_count++;
	node = &ctx->nodes[node_i];
	node->bounds = bounds_of_range(ctx->prims, first, count);
	node->first = first;
	node->count = count;
	node->left = -1;
	node->right = -1;
	return (node_i);
}

static int	build_recursive(t_build_ctx *ctx, int first, int count)
{
	int			node_i;
	int			left_count;
	int			axis;
	t_bvh_node	*node;

	node_i = init_node(ctx, first, count);
	if (node_i < 0)
		return (-1);
	node = &ctx->nodes[node_i];
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
	node->right = build_recursive(ctx, first + left_count, count - left_count);
	if (node->left < 0 || node->right < 0)
		return (-1);
	return (node_i);
}

t_bvh	*bvh_build(t_bvh_prim *prims, int prim_count)
{
	t_bvh		*bvh;
	t_build_ctx	ctx;

	if (prim_count <= 0)
		return (NULL);
	bvh = allocate_bvh(prim_count);
	if (!bvh)
		return (NULL);
	ctx.prims = prims;
	ctx.nodes = bvh->nodes;
	ctx.node_count = 0;
	ctx.node_cap = prim_count * 2;
	bvh->root = build_recursive(&ctx, 0, prim_count);
	if (bvh->root < 0)
	{
		bvh_free(bvh);
		return (NULL);
	}
	bvh->node_count = ctx.node_count;
	bvh->prim_count = prim_count;
	fill_prim_indices(bvh, prims, prim_count);
	return (bvh);
}
