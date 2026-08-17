/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:50:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by fbenini-         ###   ########.fr       */
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

#define EPSILON 1e-6f

static void	set_hit_geometry(t_moller_trumbore_params calc, t_triangle tri,
		t_hit *hit)
{
	float	barycenter;

	if (calc.ray_time < hit->ray_time)
	{
		barycenter = 1.0f - calc.bary_coords.v - calc.bary_coords.u;

		calc.raydir_cross_edge2 = vec3_normalize(vec3_add(
					vec3_mul(tri.n[0], barycenter),
					vec3_add(vec3_mul(tri.n[2], calc.bary_coords.v),
						vec3_mul(tri.n[1], calc.bary_coords.u))));
		hit->ray_time = calc.ray_time;
		hit->point_local = vec3_add(tri.v[0], vec3_add(vec3_mul(calc.edge1,
						calc.bary_coords.u), vec3_mul(calc.edge2,
						calc.bary_coords.v)));
		hit->normal_local = calc.raydir_cross_edge2;
		hit->hit_something = 1;
	}
}

char	intersect_triangle(t_vec3 ray_dir, t_vec3 ray_pos, t_triangle tri,
		t_hit *hit)
{
	t_moller_trumbore_params	calc;

	calc.edge1 = vec3_sub(tri.v[1], tri.v[0]);
	calc.edge2 = vec3_sub(tri.v[2], tri.v[0]);
	calc.raydir_cross_edge2 = vec3_cross(ray_dir, calc.edge2);
	calc.det = vec3_dot(calc.edge1, calc.raydir_cross_edge2);
	if (fabsf(calc.det) < EPSILON)
		return (0);
	calc.inv_det = 1.0f / calc.det;
	calc.ray_length = vec3_sub(ray_pos, tri.v[0]);
	calc.bary_coords.u = vec3_dot(calc.ray_length, calc.raydir_cross_edge2)
		* calc.inv_det;
	if (calc.bary_coords.u < 0.0f || calc.bary_coords.u > 1.0f)
		return (0);
	calc.raylength_cross_edge1 = vec3_cross(calc.ray_length, calc.edge1);
	calc.bary_coords.v = vec3_dot(ray_dir, calc.raylength_cross_edge1)
		* calc.inv_det;
	if (calc.bary_coords.v < 0.0f
		|| calc.bary_coords.u + calc.bary_coords.v > 1.0f)
		return (0);
	calc.ray_time = vec3_dot(calc.edge2, calc.raylength_cross_edge1)
		* calc.inv_det;
	if (calc.ray_time < EPSILON)
		return (0);
	if (hit != NULL)
		set_hit_geometry(calc, tri, hit);
	return (1);
}

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
	t_hit	hit;
	t_vec3	ray_dir;

	t_vec3	world_point;
	t_vec3	world_normal;
	t_vec3	view_dir;
	t_vec3	color;

	hit.ray_time = INFINITY;
	hit.hit_something = 0;
	hit.mesh = NULL;
	ray_dir = get_ray_dir(range_map_cam_coord(x, 0, program.window_width),
			range_map_cam_coord(y, 0, program.window_height), scene.camera,
			program);
	intersect_scene(scene, ray_dir, &hit);
	if (!hit.hit_something)
		return (vec_to_hex(scene.ambient.color));
	world_point = local_to_world_point(hit.point_local, &hit);
	world_normal = local_to_world_normal(hit.normal_local, &hit);
	view_dir = vec3_normalize(vec3_sub(scene.camera.position, world_point));
	color = shade_blinn_phong(world_point, world_normal, view_dir,
			hit.mesh->material, scene, hit.mesh);
	return (vec_to_color(color));
}
