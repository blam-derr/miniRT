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

// Moller Trumbore algorhitm
#define EPSILON 1e-6f

char	intersect_triangle(
	t_vec3 ray_dir,
	t_vec3 ray_pos,
	t_triangle triangle,
	unsigned int *color)
{
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	p;
	t_vec3	s;
	t_vec3	q;
	float	det;
	float	inv;
	float	u;
	float	v;
	float	t;

	e1 = vec3_sub(triangle.v[1], triangle.v[0]);
	e2 = vec3_sub(triangle.v[2], triangle.v[0]);
	p = vec3_cross(ray_dir, e2);
	det = vec3_dot(e1, p);
	if (fabsf(det) < EPSILON)
		return (0);
	inv = 1.0f / det;
	s = vec3_sub(ray_pos, triangle.v[0]);
	u = vec3_dot(s, p) * inv;
	if (u < 0.0f || u > 1.0f)
		return (0);
	q = vec3_cross(s, e1);
	v = vec3_dot(ray_dir, q) * inv;
	if (v < 0.0f || (u + v) > 1.0f)
		return (0);
	t = vec3_dot(e2, q) * inv;
	if (t < EPSILON)
		return (0);
	*color = 0x00FF00;
	return (1);
}
unsigned int	trace_ray(int x, int y, t_scene scene, t_program program)
{
	t_vec3		ray_dir;
	float		u;
	float		v;
	t_triangle	triangle;
	unsigned int	color;

	color = vec_to_hex(scene.ambient.color);
	triangle.v[0] = (t_vec3){-5.0f, -5.0f, 20.0f};
	triangle.v[1] = (t_vec3){ 5.0f, -5.0f, 20.0f};
	triangle.v[2] = (t_vec3){ 0.0f,  5.0f, 20.0f};
	u = range_map_cam_coord(x, 0, program.window_width);
	v = range_map_cam_coord(y, 0, program.window_height);
	ray_dir = get_ray_dir(u, v, scene.camera);
	intersect_triangle(ray_dir, scene.camera.position, triangle, &color);
	return (color);
}
