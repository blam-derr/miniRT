/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:50:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/31 21:32:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft.h"
#include "mesh.h"
#include "miniRT.h"
#include "ray.h"
#include "scene.h"
#include "triangle.h"
#include "utils.h"
#include "vec.h"

#define EPSILON 1e-6

static void	set_hit_geometry(t_tri_params v, t_triangle tri, t_hit *hit)
{
	float	barycenter;

	if (v.t < hit->ray_time)
	{
		barycenter = 1.0f - v.v - v.u;
		v.normal = vec3_normalize(vec3_add(vec3_mul(tri.n[0], barycenter),
				vec3_add(vec3_mul(tri.n[2], v.v), vec3_mul(tri.n[1], v.u))));
		hit->ray_time = v.t;
		hit->point_local = vec3_add(tri.v[0],
				vec3_add(vec3_mul(v.edge1, v.u),
					vec3_mul(v.edge2, v.v)));
		hit->normal_local = v.normal;
		hit->hit_something = 1;
	}
}

static char	intersect_triangle(t_vec3 ray_dir, t_vec3 ray_pos, t_triangle tri,
		t_hit *hit)
{
	t_tri_params	v;

	v.edge1 = vec3_sub(tri.v[1], tri.v[0]);
	v.edge2 = vec3_sub(tri.v[2], tri.v[0]);
	v.pvec = vec3_cross(ray_dir, v.edge2);
	v.det = vec3_dot(v.edge1, v.pvec);
	if (fabsf(v.det) < EPSILON)
		return (0);
	v.inv_det = 1.0f / v.det;
	v.tvec = vec3_sub(ray_pos, tri.v[0]);
	v.u = vec3_dot(v.tvec, v.pvec) * v.inv_det;
	if (v.u < 0.0f || v.u > 1.0f)
		return (0);
	v.qvec = vec3_cross(v.tvec, v.edge1);
	v.v = vec3_dot(ray_dir, v.qvec) * v.inv_det;
	if (v.v < 0.0f || v.u + v.v > 1.0f)
		return (0);
	v.t = vec3_dot(v.edge2, v.qvec) * v.inv_det;
	if (v.t < EPSILON)
		return (0);
	set_hit_geometry(v, tri, hit);
	return (1);
}

static char	*intersect_scene(t_scene scene, t_vec3 ray_dir, t_hit *hit)
{
	t_list	*objs_in_scene;
	size_t	i;
	t_mesh	*mesh;
	t_vec3	ray_pos_local;
	t_vec3	ray_dir_local;
	t_vec3	world_up;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	local_mesh_position;
	float	prev_hit;

	objs_in_scene = scene.objects;
	while (objs_in_scene)
	{
		mesh = (t_mesh *)objs_in_scene->content;
		if (vec3_length(mesh->dir) < EPSILON)
			forward = vec3_create(0, 1, 0);
		else
			forward = vec3_normalize(mesh->dir);
		if (fabsf(forward.y) > 0.999f)
			world_up = vec3_create(1, 0, 0);
		else
			world_up = vec3_create(0, 1, 0);
		right = vec3_normalize(vec3_cross(world_up, forward));
		up = vec3_cross(forward, right);
		local_mesh_position = vec3_sub(scene.camera.position, mesh->pos);
		ray_pos_local.x = vec3_dot(local_mesh_position, right);
		ray_pos_local.y = vec3_dot(local_mesh_position, forward);
		ray_pos_local.z = vec3_dot(local_mesh_position, up);
		ray_dir_local.x = vec3_dot(ray_dir, right);
		ray_dir_local.y = vec3_dot(ray_dir, forward);
		ray_dir_local.z = vec3_dot(ray_dir, up);
		ray_dir_local = vec3_normalize(ray_dir_local);
		i = 0;
		prev_hit = hit->ray_time;
		while (i < mesh->triangle_count)
		{
			intersect_triangle(ray_dir_local, ray_pos_local,
				mesh->triangles[i], hit);
			i++;
		}
		if (hit->ray_time < prev_hit)
		{
			hit->basis_forward = forward;
			hit->basis_right = right;
			hit->basis_up = up;
			hit->mesh = mesh;
		}
		objs_in_scene = objs_in_scene->next;
	}
	return (0);
}

unsigned int	trace_ray(int x, int y, t_scene scene, t_program program)
{
	t_hit	hit;
	t_vec3	ray_dir;

	hit.ray_time = INFINITY;
	hit.hit_something = 0;
	ray_dir = get_ray_dir(range_map_cam_coord(x, 0, program.window_width),
			range_map_cam_coord(y, 0, program.window_height), scene.camera,
			program);
	intersect_scene(scene, ray_dir, &hit);
	if (hit.hit_something)
	{
		t_vec3	world_normal = local_to_world_normal(hit.normal_local, &hit);
		t_vec3 color_res = vec3_mul(world_normal, 0.5);
		color_res = vec3_add_by_scalar(color_res, 0.5);
		color_res = vec3_mul(color_res, 255.0f);
		return (vec_to_hex(color_res));
	}
	return (vec_to_hex(scene.ambient.color));
}
