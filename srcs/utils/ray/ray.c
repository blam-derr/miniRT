/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:50:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/01 16:28:58 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <math.h>
#include "camera.h"
#include "mesh.h"
#include "miniRT.h"
#include "scene.h"
#include "utils.h"
#include "vec.h"
#include "triangle.h"

#define EPSILON 1e-6

static void	set_hit_color(t_tri_params *v, t_triangle tri, t_hit *hit)
{
	float	w;

	w = 1.0f - v->v - v->u;
	v->normal = vec3_add(
			vec3_mul(tri.n[0], w),
			vec3_add(
				vec3_mul(tri.n[2], v->v),
				vec3_mul(tri.n[1], v->u)));
	v->rgb[0] = (v->normal.x + 1.0f) * 127.5f;
	v->rgb[1] = (v->normal.y + 1.0f) * 127.5f;
	v->rgb[2] = (v->normal.z + 1.0f) * 127.5f;
	if (v->t < hit->t)
	{
		hit->t = v->t;
		hit->color = ((unsigned char)v->rgb[0] << 16)
			| ((unsigned char)v->rgb[1] << 8)
			| (unsigned char)v->rgb[2];
	}
}

static char	intersect_triangle(
		t_vec3 ray_dir,
		t_vec3 ray_pos,
		t_triangle tri,
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

static t_vec3	get_ray_dir(
		float x, float y, t_camera camera, t_program program)
{
	float	aspect;
	float	scale;
	t_vec3	ray;

	aspect = (float)program.window_width / (float)program.window_height;
	scale = tanf(camera.fov * 0.5f * (M_PI / 180.0f));
	ray = vec3_add(
			camera.forward,
			vec3_add(
				vec3_mul(camera.right, x * aspect * scale),
				vec3_mul(camera.up, y * scale)));
	return (vec3_normalize(ray));
}

unsigned int	trace_ray(int x, int y, t_scene scene, t_program program)
{
	t_vec3			ray_dir;
	unsigned int	color;
	size_t			i;
	t_hit			hit;

	color = vec_to_hex(scene.ambient.color);
	i = 0;
	hit.t = INFINITY;
	ray_dir = get_ray_dir(
			range_map_cam_coord(x, 0, program.window_width),
			range_map_cam_coord(y, 0, program.window_height),
			scene.camera, program);
	while (i < scene.sphere.triangle_count)
	{
		intersect_triangle(ray_dir, scene.camera.position,
			scene.sphere.triangles[i], &hit);
		i++;
	}
	if (hit.t != INFINITY)
		color = hit.color;
	return (color);
}
