/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 13:44:43 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include <math.h>

t_aabb	aabb_empty(void)
{
	t_aabb	box;

	box.min = vec3_create(INFINITY, INFINITY, INFINITY);
	box.max = vec3_create(-INFINITY, -INFINITY, -INFINITY);
	return (box);
}

t_aabb	aabb_from_point(t_vec3 p)
{
	t_aabb	box;

	box.min = p;
	box.max = p;
	return (box);
}

void	aabb_expand_point(t_aabb *box, t_vec3 p)
{
	if (p.x < box->min.x)
		box->min.x = p.x;
	if (p.y < box->min.y)
		box->min.y = p.y;
	if (p.z < box->min.z)
		box->min.z = p.z;
	if (p.x > box->max.x)
		box->max.x = p.x;
	if (p.y > box->max.y)
		box->max.y = p.y;
	if (p.z > box->max.z)
		box->max.z = p.z;
}

void	aabb_expand_aabb(t_aabb *box, t_aabb other)
{
	aabb_expand_point(box, other.min);
	aabb_expand_point(box, other.max);
}

t_vec3	aabb_centroid(t_aabb box)
{
	return (vec3_mul(vec3_add(box.min, box.max), 0.5f));
}
