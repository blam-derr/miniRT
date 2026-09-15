/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:50:37 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:45:47 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_bonus.h"
#include "miniRT_bonus.h"
#include "ray_bonus.h"
#include "scene_bonus.h"
#include "triangle_bonus.h"
#include "utils_bonus.h"
#include "vec_bonus.h"
#include <math.h>

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
	t_vec3	ray_dir;
	t_ray	ray;
	t_vec3	color;

	ray_dir = get_ray_dir(range_map_cam_coord(x, 0, program.window_width),
			range_map_cam_coord(y, 0, program.window_height), scene.camera,
			program);
	ray = ray_make(scene.camera.position, ray_dir, EPSILON, INFINITY);
	color = trace_ray_recursive(scene, ray, MAX_REFLECT_DEPTH);
	return (vec_to_color(color));
}
