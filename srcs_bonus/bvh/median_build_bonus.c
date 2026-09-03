/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"

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

t_aabb	bounds_of_range(t_bvh_prim *prims, int first, int count)
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

t_aabb	centroid_bounds(t_bvh_prim *prims, int first, int count)
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

int	partition_mid(t_bvh_prim *prims, int first, int count, int axis)
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
