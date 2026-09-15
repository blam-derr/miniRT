/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/14 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"
#include "ray_bonus.h"
#include "scene_bonus.h"
#include "utils_bonus.h"
#include "vec_bonus.h"
#include <math.h>
#include <stdio.h>

static t_hit	init_hit(void)
{
	t_hit	hit;

	hit.ray_time = INFINITY;
	hit.hit_something = 0;
	hit.mesh = NULL;
	return (hit);
}

static void	intersect_ray(t_scene scene, t_ray ray, t_hit *hit)
{
	if (!scene.accel)
		return ;
	hit->ray_time = ray.tmax;
	intersect_tlas(scene.accel, &ray, hit);
}

static t_vec3	reflected_dir(t_vec3 dir, t_vec3 normal)
{
	return (vec3_normalize(vec3_sub(dir,
				vec3_mul(normal, 2.0f * vec3_dot(dir, normal)))));
}

static t_ray	make_reflect_ray(t_ray ray, t_world_translated world)
{
	t_vec3	dir;
	t_vec3	normal;
	t_vec3	origin;
	float	bias;

	normal = world.geometric_normal;
	if (vec3_dot(normal, ray.dir) >= 0.0f)
		normal = vec3_mul(normal, -1.0f);
	dir = reflected_dir(ray.dir, world.normal);
	bias = fmaxf(EPSILON, 1e-3 * vec3_length(world.point));
	origin = vec3_add(world.point, vec3_mul(normal, bias));
	return (ray_make(origin, dir, EPSILON, INFINITY));
}

t_vec3	trace_ray_recursive(t_scene scene, t_ray ray, int depth)
{
	t_hit				hit;
	t_world_translated	world;
	t_vec3				local;
	t_vec3				reflected;
	float				k;

	hit = init_hit();
	intersect_ray(scene, ray, &hit);
	if (!hit.hit_something)
		return (vec3_div(scene.ambient.color, 255.0f));
	world.point = local_to_world_point(hit.point_local, &hit);
	world.normal = local_to_world_normal(hit.normal_local, &hit);
	world.geometric_normal = local_to_world_normal(
			hit.geometric_normal_local, &hit);
	local = shade_blinn_phong(world, vec3_mul(ray.dir, -1.0f),
			scene, hit.mesh);
	k = hit.mesh->material.reflectivity;
	if (depth <= 0 || k <= 0.0f)
		return (local);
	reflected = trace_ray_recursive(scene, make_reflect_ray(ray, world),
			depth - 1);
	return (vec3_add(vec3_mul(local, 1.0f - k), vec3_mul(reflected, k)));
}
