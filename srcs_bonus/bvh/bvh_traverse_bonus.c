/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_traverse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:46:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"

void	bvh_push(t_bvh_traversal *tr, int node, float t)
{
	if (tr->sp >= BVH_STACK_SIZE)
		return ;
	tr->stack[tr->sp].node = node;
	tr->stack[tr->sp].t_enter = t;
	tr->sp++;
}

void	bvh_traverse_children(t_bvh_traversal *tr, t_ray *ray,
		t_bvh_node *node)
{
	float	t_enter;

	if (node->left >= 0)
	{
		if (ray_aabb_intersect(ray, tr->bvh->nodes[node->left].bounds,
				&t_enter))
			bvh_push(tr, node->left, t_enter);
	}
	if (node->right >= 0)
	{
		if (ray_aabb_intersect(ray, tr->bvh->nodes[node->right].bounds,
				&t_enter))
			bvh_push(tr, node->right, t_enter);
	}
}
