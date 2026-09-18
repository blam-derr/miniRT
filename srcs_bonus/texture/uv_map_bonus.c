/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_map_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/17 20:33:51 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_bonus.h"
#include "scene_bonus.h"
#include "vec_bonus.h"
#include <math.h>

static float	wrap_unit(float value)
{
	value = fmodf(value, 1.0f);
	if (value < 0.0f)
		value += 1.0f;
	return (value);
}

static t_vec2	map_sphere_uv(t_vec3 point)
{
	t_vec2	uv;
	float	radius;

	radius = vec3_length(point);
	if (radius < EPSILON)
		return ((t_vec2){0.5f, 0.5f});
	uv.u = 0.5f + atan2f(point.z, point.x) / (2.0f * M_PI);
	uv.v = acosf(fmaxf(-1.0f, fminf(1.0f, point.y / radius))) / M_PI;
	return (uv);
}

static t_vec2	map_cylinder_uv(t_vec3 point, t_vec3 normal, t_mesh *mesh)
{
	t_vec2	uv;
	float	radius;
	float	range_y;

	radius = sqrtf(point.x * point.x + point.z * point.z);
	if (fabsf(normal.y) > 0.5f)
	{
		if (radius < EPSILON)
			return (create_vec2(0.5f, 0.5f));
		uv.u = point.x / (2.0f * radius) + 0.5f;
		uv.v = point.z / (2.0f * radius) + 0.5f;
		return (uv);
	}
	range_y = mesh->local_bounds.max.y - mesh->local_bounds.min.y;
	uv.u = 0.5f + atan2f(point.z, point.x) / (2.0f * M_PI);
	if (range_y > EPSILON)
		uv.v = (point.y - mesh->local_bounds.min.y) / range_y;
	else
		uv.v = 0.5f;
	return (uv);
}

static t_vec2	map_planar_uv(t_vec3 point, t_vec3 normal, float scale)
{
	t_vec2	uv;

	if (fabsf(normal.x) >= fabsf(normal.y)
		&& fabsf(normal.x) >= fabsf(normal.z))
	{
		uv.u = wrap_unit(point.y * scale);
		uv.v = wrap_unit(point.z * scale);
	}
	else if (fabsf(normal.y) >= fabsf(normal.z))
	{
		uv.u = wrap_unit(point.x * scale);
		uv.v = wrap_unit(point.z * scale);
	}
	else
	{
		uv.u = wrap_unit(point.x * scale);
		uv.v = wrap_unit(point.y * scale);
	}
	return (uv);
}

t_vec2	get_mesh_uv(t_mesh *mesh, t_vec3 point_local, t_vec3 normal_local)
{
	t_vec2	uv;
	float	scale;
	float	range_x;
	float	range_z;

	scale = mesh->material.texture_scale;
	if (scale <= 0.0f)
		scale = 1.0f;
	if (mesh->shape == SHAPE_SPHERE)
		return (map_sphere_uv(point_local));
	if (mesh->shape == SHAPE_CYLINDER)
		return (map_cylinder_uv(point_local, normal_local, mesh));
	if (mesh->shape == SHAPE_PLANE)
	{
		range_x = mesh->local_bounds.max.x - mesh->local_bounds.min.x;
		range_z = mesh->local_bounds.max.z - mesh->local_bounds.min.z;
		uv.u = wrap_unit(((point_local.x - mesh->local_bounds.min.x)
					/ range_x) * scale);
		uv.v = wrap_unit(((point_local.z - mesh->local_bounds.min.z)
					/ range_z) * scale);
		return (uv);
	}
	return (map_planar_uv(point_local, normal_local, scale));
}
