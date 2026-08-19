/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_metrics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 15:35:47 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/18 15:43:13 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include <math.h>

float	aabb_surface_area(t_aabb box)
{
	float	dx;
	float	dy;
	float	dz;

	dx = box.max.x - box.min.x;
	dy = box.max.y - box.min.y;
	dz = box.max.z - box.min.z;
	if (dx < 0.0f || dy < 0.0f || dz < 0.0f)
		return (0.0f);
	return (2.0f * (dx * dy + dy * dz + dz * dx));
}

int	aabb_longest_axis(t_aabb box)
{
	float	dx;
	float	dy;
	float	dz;

	dx = box.max.x - box.min.x;
	dy = box.max.y - box.min.y;
	dz = box.max.z - box.min.z;
	if (dx > dy && dx > dz)
		return (0);
	if (dy > dz)
		return (1);
	return (2);
}

t_aabb	aabb_transform(t_aabb local, t_vec3 pos, t_local_dirs dirs)
{
	t_aabb	world;
	t_vec3	c;
	t_vec3	e;
	t_vec3	wc;
	t_vec3	we;

	c = aabb_centroid(local);
	e = vec3_mul(vec3_sub(local.max, local.min), 0.5f);
	wc = vec3_add(pos, vec3_add(vec3_mul(dirs.right, c.x),
				vec3_add(vec3_mul(dirs.forward, c.y), vec3_mul(dirs.up, c.z))));
	we.x = fabsf(dirs.right.x) * e.x + fabsf(dirs.forward.x)
		* e.y + fabsf(dirs.up.x) * e.z;
	we.y = fabsf(dirs.right.y) * e.x + fabsf(dirs.forward.y)
		* e.y + fabsf(dirs.up.y) * e.z;
	we.z = fabsf(dirs.right.z) * e.x + fabsf(dirs.forward.z)
		* e.y + fabsf(dirs.up.z) * e.z;
	world.min = vec3_sub(wc, we);
	world.max = vec3_add(wc, we);
	return (world);
}
