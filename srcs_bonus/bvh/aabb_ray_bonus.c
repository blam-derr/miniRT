/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 13:43:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:46:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <complex.h>
#include <math.h>
#include "aabb_bonus.h"
#define ORIGIN 0
#define INV 1

static float	safe_inv(float v)
{
	if (fabsf(v) < 1e-8)
	{
		if (v >= 0.0f)
			return (1e8);
		return (-1e8);
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

static void	slab_axis(float *ray_values, float bmin, float bmax, float *t)
{
	float	tmin;
	float	tmax;
	float	tmp;

	tmin = (bmin - ray_values[ORIGIN]) * ray_values[INV];
	tmax = (bmax - ray_values[ORIGIN]) * ray_values[INV];
	if (ray_values[INV] < 0.0f)
	{
		tmp = tmin;
		tmin = tmax;
		tmax = tmp;
	}
	if (tmin > t[0])
		t[0] = tmin;
	if (tmax < t[1])
		t[1] = tmax;
}

int	ray_aabb_intersect(const t_ray *ray, t_aabb box, float *t_enter)
{
	float	t[2];
	float	ray_values[2];

	t[0] = ray->tmin;
	t[1] = ray->tmax;
	ray_values[ORIGIN] = ray->origin.x;
	ray_values[INV] = ray->inv_dir.x;
	slab_axis(ray_values, box.min.x, box.max.x, t);
	if (t[0] > t[1])
		return (0);
	ray_values[ORIGIN] = ray->origin.y;
	ray_values[INV] = ray->inv_dir.y;
	slab_axis(ray_values, box.min.y, box.max.y, t);
	if (t[0] > t[1])
		return (0);
	ray_values[ORIGIN] = ray->origin.z;
	ray_values[INV] = ray->inv_dir.z;
	slab_axis(ray_values, box.min.z, box.max.z, t);
	if (t[0] > t[1])
		return (0);
	*t_enter = t[0];
	return (1);
}
