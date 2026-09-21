/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/21 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_bonus.h"
#include "utils_bonus.h"
#include "vec_bonus.h"
#include <math.h>

static float	height_at(t_texture *bump, t_vec2 uv)
{
	t_vec3	color;

	color = sample_texture(bump, uv);
	return (0.2126f * color.x + 0.7152f * color.y + 0.0722f * color.z);
}

static t_vec3	tangent_from_normal(t_vec3 normal)
{
	t_vec3	ref;
	t_vec3	tangent;

	if (fabsf(normal.y) < 0.9f)
		ref = vec3_create(0, 1, 0);
	else
		ref = vec3_create(1, 0, 0);
	tangent = vec3_cross(normal, ref);
	return (vec3_normalize(tangent));
}

static t_vec2	height_gradient(t_texture *bump, t_vec2 uv, t_vec2 duv)
{
	t_vec2	grad;

	grad.u = height_at(bump, create_vec2(uv.u + duv.u, uv.v))
		- height_at(bump, create_vec2(uv.u - duv.u, uv.v));
	grad.v = height_at(bump, create_vec2(uv.u, uv.v + duv.v))
		- height_at(bump, create_vec2(uv.u, uv.v - duv.v));
	return (grad);
}

static t_vec3	perturb_normal(t_vec3 normal, t_vec3 tangent,
		t_vec3 bitangent, t_vec2 grad)
{
	t_vec3	perturbation;
	t_vec3	res;

	perturbation = vec3_add(vec3_mul(tangent, grad.u),
			vec3_mul(bitangent, grad.v));
	res = vec3_normalize(vec3_sub(normal, perturbation));
	return (res);
}

t_vec3	get_bumped_normal(t_mesh *mesh, t_vec3 point_local,
		t_vec3 normal_local)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec2	uv;
	t_vec2	duv;
	t_vec2	grad;

	if (!mesh->material.has_bump || !mesh->material.bump.addr
		|| mesh->material.bump.width <= 0 || mesh->material.bump.height <= 0)
		return (normal_local);
	uv = get_mesh_uv(mesh, point_local, normal_local);
	duv.u = 1.0f / (float)mesh->material.bump.width;
	duv.v = 1.0f / (float)mesh->material.bump.height;
	grad = height_gradient(&mesh->material.bump, uv, duv);
	grad = create_vec2(grad.u * mesh->material.bump_strength,
			grad.v * mesh->material.bump_strength);
	tangent = tangent_from_normal(normal_local);
	bitangent = vec3_cross(normal_local, tangent);
	return (perturb_normal(normal_local, tangent, bitangent, grad));
}
