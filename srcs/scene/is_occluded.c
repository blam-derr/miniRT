/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_occluded.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "ray.h"
#include "scene.h"
#include <math.h>

#define EPSILON 1e-6f

char	is_any_triangle_intersected(t_vec3 ray_dir, t_vec3 ray_pos,
		t_triangle tri, float max_t)
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
	if (calc.ray_time < EPSILON || calc.ray_time > max_t)
		return (0);
	return (1);
}

char	is_occluded(t_scene scene, t_vec3 origin, t_vec3 dir, float max_t,
		t_mesh *ignore_mesh)
{
	t_ray	ray;

	if (!scene.accel)
		return (0);
	ray = ray_make(origin, dir, EPSILON, max_t);
	return ((char)tlas_any_hit(scene.accel, &ray, ignore_mesh));
}
