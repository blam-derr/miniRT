/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:50:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/22 09:59:01 by jode-cas         ###   ########.fr       */
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
#include <math.h>
#include <stddef.h>

#define EPSILON 1e-6

static void	set_hit_color(t_tri_params *v, t_triangle tri, t_hit *hit)
{
	float	barycenter;

	barycenter = 1.0f - v->v - v->u;
	v->normal = vec3_add(vec3_mul(tri.n[0], barycenter),
			vec3_add(vec3_mul(tri.n[2], v->v), vec3_mul(tri.n[1], v->u)));
	v->rgb[0] = (v->normal.x + 1.0f) * 127.5f;
	v->rgb[1] = (v->normal.y + 1.0f) * 127.5f;
	v->rgb[2] = (v->normal.z + 1.0f) * 127.5f;
	if (v->t < hit->ray_time)
	{
		hit->ray_time = v->t;
		hit->color = ((unsigned char)v->rgb[0] << 16) | ((unsigned char)v->rgb[1] << 8) | (unsigned char)v->rgb[2];
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
	set_hit_color(&v, tri, hit);
	return (1);
}

static t_vec3	get_ray_dir(float x, float y, t_camera camera,
		t_program program)
{
	float	aspect;
	float	scale;
	t_vec3	ray;

	aspect = (float)program.window_width / (float)program.window_height;
	scale = tanf(camera.fov * 0.5f * (M_PI / 180.0f));
	ray = vec3_add(camera.forward, vec3_add(vec3_mul(camera.right, x * aspect
					* scale), vec3_mul(camera.up, y * scale)));
	return (vec3_normalize(ray));
}

static char	*intersect_scene(t_scene scene, t_vec3 ray_dir, t_hit *hit)
{
	t_list	*lst;
	size_t	i;
	t_mesh	*mesh;
	t_vec3	ray_pos_local;
	t_vec3	ray_dir_local;
	t_vec3	world_up;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	p;

	lst = scene.objects;
	while (lst)
	{
		mesh = (t_mesh *)lst->content;
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
		p = vec3_sub(scene.camera.position, mesh->pos);
		ray_pos_local.x = vec3_dot(p, right);
		ray_pos_local.y = vec3_dot(p, forward);
		ray_pos_local.z = vec3_dot(p, up);
		ray_dir_local.x = vec3_dot(ray_dir, right);
		ray_dir_local.y = vec3_dot(ray_dir, forward);
		ray_dir_local.z = vec3_dot(ray_dir, up);
		ray_dir_local = vec3_normalize(ray_dir_local);
		i = 0;
		while (i < mesh->triangle_count)
		{
			if (intersect_triangle(ray_dir_local, ray_pos_local,
					mesh->triangles[i], hit))
				hit->mesh_pos = mesh->pos;
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

unsigned int	trace_ray(int x, int y, t_scene scene, t_program program)
{
	unsigned int	color;
	t_hit			hit;
	t_vec3			ray_dir;

	color = vec_to_hex(scene.ambient.color);
	hit.ray_time = INFINITY;
	ray_dir = get_ray_dir(range_map_cam_coord(x, 0, program.window_width),
			range_map_cam_coord(y, 0, program.window_height), scene.camera,
			program);
	intersect_scene(scene, ray_dir, &hit);
	if (hit.ray_time != INFINITY)
		return (hit.color);
	return (color);
}
