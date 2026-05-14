/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:50:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/05/12 21:09:26 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "miniRT.h"
#include "scene.h"
#include "utils.h"
#include "vec.h"
#include "triangle.h"
#define EPSILON 1e-6

static char	check_barycentric(float u, float v)
{
	if (u < 0.0f || u > 1.0f)
		return (0);
	if (v < 0.0f || (u + v) > 1.0f)
		return (0);
	return (1);
}

static char	check_triangle_hit(
	t_vec3 ray_dir,
	t_vec3 vals[5],
	float inv)
{
	float	v;
	float	t;

	v = vec3_dot(ray_dir, vals[4]) * inv;
	if (!check_barycentric(vals[3].x, v))
		return (0);
	t = vec3_dot(vals[1], vals[4]) * inv;
	if (t < EPSILON)
		return (0);
	return (1);
}

char	intersect_triangle(
	t_vec3 ray_dir,
	t_vec3 ray_pos,
	t_triangle tri,
	unsigned int *color)
{
	t_vec3	v[5];
	float	det;
	float	inv;

	v[0] = vec3_sub(tri.v[1], tri.v[0]);
	v[1] = vec3_sub(tri.v[2], tri.v[0]);
	v[2] = vec3_cross(ray_dir, v[1]);
	det = vec3_dot(v[0], v[2]);
	if (fabsf(det) < EPSILON)
		return (0);
	inv = 1.0f / det;
	v[3] = vec3_sub(ray_pos, tri.v[0]);
	v[3].x = vec3_dot(v[3], v[2]) * inv;
	v[4] = vec3_cross(v[3], v[0]);
	if (!check_triangle_hit(ray_dir, v, inv))
		return (0);
	*color = 0x00FF00;
	return (1);
}

static t_vec3	get_ray_dir(float x, float y, t_camera camera)
{
	t_vec3	res;
	t_vec3	multiplied_right;
	t_vec3	multiplied_up;
	t_vec3	added_vec;
	float	half_fov;

	half_fov = tanf((camera.fov / 2.0f) * (M_PI / 180.0f));
	multiplied_right = vec3_mul(camera.right, x * half_fov);
	multiplied_up = vec3_mul(camera.up, y * half_fov);
	added_vec = vec3_add(camera.forward,
			vec3_add(multiplied_up, multiplied_right));
	res = vec3_normalize(added_vec);
	return (res);
}

unsigned int	trace_ray(int x, int y, t_scene scene, t_program program)
{
	t_vec3			ray_dir;
	float			u;
	float			v;
	t_triangle		triangle;
	unsigned int	color;

	color = vec_to_hex(scene.ambient.color);
	triangle.v[0] = (t_vec3){-5.0f, 5.0f, 20.0f};
	triangle.v[1] = (t_vec3){5.0f, 5.0f, 20.0f};
	triangle.v[2] = (t_vec3){0.0f, -5.0f, 20.0f};
	u = range_map_cam_coord(x, 0, program.window_width);
	v = range_map_cam_coord(y, 0, program.window_height);
	ray_dir = get_ray_dir(u, v, scene.camera);
	intersect_triangle(ray_dir, scene.camera.position, triangle, &color);
	return (color);
}
