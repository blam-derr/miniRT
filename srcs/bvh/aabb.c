/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by fbenini-         ###   ########.fr       */
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

t_aabb	aabb_transform(t_aabb local, t_vec3 pos, t_vec3 right, t_vec3 forward,
		t_vec3 up)
{
	t_aabb	world;
	t_vec3	c;
	t_vec3	e;
	t_vec3	wc;
	t_vec3	we;

	c = aabb_centroid(local);
	e = vec3_mul(vec3_sub(local.max, local.min), 0.5f);
	wc = vec3_add(pos, vec3_add(vec3_mul(right, c.x),
				vec3_add(vec3_mul(forward, c.y), vec3_mul(up, c.z))));
	we.x = fabsf(right.x) * e.x + fabsf(forward.x) * e.y + fabsf(up.x) * e.z;
	we.y = fabsf(right.y) * e.x + fabsf(forward.y) * e.y + fabsf(up.y) * e.z;
	we.z = fabsf(right.z) * e.x + fabsf(forward.z) * e.y + fabsf(up.z) * e.z;
	world.min = vec3_sub(wc, we);
	world.max = vec3_add(wc, we);
	return (world);
}

static float	safe_inv(float v)
{
	if (fabsf(v) < 1e-8f)
	{
		if (v >= 0.0f)
			return (1e8f);
		return (-1e8f);
	}
	return (1.0f / v);
}

t_ray	ray_make(t_vec3 origin, t_vec3 dir, float tmin, float tmax)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = dir;
	ray.inv_dir.x = safe_inv(dir.x);
	ray.inv_dir.y = safe_inv(dir.y);
	ray.inv_dir.z = safe_inv(dir.z);
	ray.tmin = tmin;
	ray.tmax = tmax;
	return (ray);
}

static void	slab_axis(float origin, float inv, float bmin, float bmax,
		float *t0, float *t1)
{
	float	tmin;
	float	tmax;
	float	tmp;

	tmin = (bmin - origin) * inv;
	tmax = (bmax - origin) * inv;
	if (inv < 0.0f)
	{
		tmp = tmin;
		tmin = tmax;
		tmax = tmp;
	}
	if (tmin > *t0)
		*t0 = tmin;
	if (tmax < *t1)
		*t1 = tmax;
}

int	ray_aabb_intersect(const t_ray *ray, t_aabb box, float *t_enter)
{
	float	t0;
	float	t1;

	t0 = ray->tmin;
	t1 = ray->tmax;
	slab_axis(ray->origin.x, ray->inv_dir.x, box.min.x, box.max.x, &t0, &t1);
	if (t0 > t1)
		return (0);
	slab_axis(ray->origin.y, ray->inv_dir.y, box.min.y, box.max.y, &t0, &t1);
	if (t0 > t1)
		return (0);
	slab_axis(ray->origin.z, ray->inv_dir.z, box.min.z, box.max.z, &t0, &t1);
	if (t0 > t1)
		return (0);
	*t_enter = t0;
	return (1);
}
