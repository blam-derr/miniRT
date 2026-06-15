/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:50:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/06/15 19:02:27 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "mesh.h"
#include "miniRT.h"
#include "scene.h"
#include "utils.h"
#include "vec.h"
#include "triangle.h"
#define EPSILON 1e-6

char	intersect_triangle(
	t_vec3 ray_dir,
	t_vec3 ray_pos,
	t_triangle tri,
	unsigned int *color,
	float *hit_t)
{
    t_vec3 edge1;
    t_vec3 edge2;
    t_vec3 pvec;
    t_vec3 tvec;
    t_vec3 qvec;
    float det;
    float inv_det;
    float u;
    float v;
    float t;
	t_vec3	normal;
	float	rgb[3];

    edge1 = vec3_sub(tri.v[1], tri.v[0]);
    edge2 = vec3_sub(tri.v[2], tri.v[0]);

    pvec = vec3_cross(ray_dir, edge2);
    det = vec3_dot(edge1, pvec);

	if (fabsf(det) < EPSILON)
		return (0);

    inv_det = 1.0f / det;

    tvec = vec3_sub(ray_pos, tri.v[0]);

    u = vec3_dot(tvec, pvec) * inv_det;

	if (u < 0.0f || u > 1.0f)
		return (0);

    qvec = vec3_cross(tvec, edge1);

    v = vec3_dot(ray_dir, qvec) * inv_det;

	if (v < 0.0f || u + v > 1.0f)
		return (0);

    t = vec3_dot(edge2, qvec) * inv_det;

	if (t < EPSILON)
		return (0);
	float w;
	w = 1.0f - v - u;

	normal = vec3_add(
	    vec3_mul(tri.n[0], w),
	    vec3_add(
	        vec3_mul(tri.n[2], v),
	        vec3_mul(tri.n[1], u)
	    )
	);
	rgb[0] = (normal.x + 1.0f) * 127.5f;
	rgb[1] = (normal.y + 1.0f) * 127.5f;
	rgb[2] = (normal.z + 1.0f) * 127.5f;
	if (t < *hit_t)
	{
		*hit_t = t;
		*color = ((unsigned char)rgb[0] << 16) | ((unsigned char)rgb[1] << 8) | (unsigned char)rgb[2];
	}
	return (1);
}

static t_vec3 get_ray_dir(float x, float y, t_camera camera, t_program program)
{
    float aspect;
    float scale;
    t_vec3 ray;

    aspect = (float)program.window_width / (float)program.window_height;
    scale = tanf(camera.fov * 0.5f * (M_PI / 180.0f));
    ray = vec3_add(
        camera.forward,
        vec3_add(
            vec3_mul(camera.right, x * aspect * scale),
            vec3_mul(camera.up, y * scale)
        )
    );

    return (vec3_normalize(ray));
}

unsigned int	trace_ray(int x, int y, t_scene scene, t_program program)
{
	t_vec3			ray_dir;
	float			u;
	float			v;
	unsigned int	color;

	color = vec_to_hex(scene.ambient.color);
	u = range_map_cam_coord(x, 0, program.window_width);
	v = range_map_cam_coord(y, 0, program.window_height);
	ray_dir = get_ray_dir(u, v, scene.camera, program);
	size_t	i = 0;
	float	hit = INFINITY;
	while (i < scene.sphere.triangle_count)
	{
		intersect_triangle(ray_dir, scene.camera.position, scene.sphere.triangles[i], &color, &hit);
		i++;
	}
	return (color);
}
