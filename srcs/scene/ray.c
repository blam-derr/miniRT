/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:50:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/17 18:58:14 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "camera.h"
#include "miniRT.h"
#include "ray.h"
#include "scene.h"
#include "triangle.h"
#include "utils.h"
#include "vec.h"
#include <math.h>

static void	intersect_scene(t_scene scene, t_vec3 ray_dir, t_hit *hit)
{
	t_ray	ray;

	if (!scene.accel)
		return ;
	ray = ray_make(scene.camera.position, ray_dir, EPSILON, INFINITY);
	hit->ray_time = ray.tmax;
	intersect_tlas(scene.accel, &ray, hit);
}

static int	clamp_color(float c)
{
	if (c < 0.0f)
		c = 0.0f;
	if (c > 1.0f)
		c = 1.0f;
	return ((int)(c * 255.0f + 0.5f));
}

static uint32_t	vec_to_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = clamp_color(color.x);
	g = clamp_color(color.y);
	b = clamp_color(color.z);
	return ((r << 16) | (g << 8) | b);
}

unsigned int	trace_ray(int x, int y, t_scene scene, t_program program)
{
	t_hit				hit;
	t_vec3				ray_dir;
	t_world_translated	world;
	t_vec3				view_dir;
	t_vec3				color;

	hit.ray_time = INFINITY;
	hit.hit_something = 0;
	hit.mesh = NULL;
	ray_dir = get_ray_dir(range_map_cam_coord(x, 0, program.window_width),
			range_map_cam_coord(y, 0, program.window_height), scene.camera,
			program);
	intersect_scene(scene, ray_dir, &hit);
	if (!hit.hit_something)
		return (vec_to_hex(scene.ambient.color));
	world.point = local_to_world_point(hit.point_local, &hit);
	world.normal = local_to_world_normal(hit.normal_local, &hit);
	view_dir = vec3_normalize(vec3_sub(scene.camera.position, world.point));
	color = shade_blinn_phong(world, view_dir, scene, hit.mesh);
	return (vec_to_color(color));
}
