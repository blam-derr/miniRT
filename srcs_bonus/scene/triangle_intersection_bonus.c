/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:37:12 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/17 19:20:49 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle_bonus.h"
#include "ray_bonus.h"
#include "scene_bonus.h"

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

static char	is_bary_coords_inside_triangle(t_barycenter coords)
{
	if (coords.v < 0.0f
		|| coords.u + coords.v > 1.0f)
		return (0);
	return (1);
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
	if (!is_bary_coords_inside_triangle(calc.bary_coords))
		return (0);
	calc.ray_time = vec3_dot(calc.edge2, calc.raylength_cross_edge1)
		* calc.inv_det;
	if (calc.ray_time < EPSILON)
		return (0);
	set_hit_geometry(calc, tri, hit);
	return (1);
}

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
	if (!is_bary_coords_inside_triangle(calc.bary_coords))
		return (0);
	calc.ray_time = vec3_dot(calc.edge2, calc.raylength_cross_edge1)
		* calc.inv_det;
	if (calc.ray_time < EPSILON || calc.ray_time > max_t)
		return (0);
	return (1);
}
