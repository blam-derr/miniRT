/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blinn_phong_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:41:08 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/17 20:40:01 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb_bonus.h"
#include "mesh_bonus.h"
#include "scene_bonus.h"
#include "utils_bonus.h"
#include "vec_bonus.h"
#include <math.h>

static t_vec3	calc_color_hit_by_light(t_blimm_phong_params bp,
		t_light light)
{
	t_vec3	light_ci;
	t_vec3	color;

	light_ci = vec3_mul(light.color, light.intensity);
	color = vec3_mul_vec3(bp.mat.color,
			vec3_mul(light_ci,
				bp.diffuse * bp.mat.diffuse_coefficient));
	color = vec3_add(color,
			vec3_mul(light_ci,
				bp.spec * bp.mat.specular_coefficient));
	return (color);
}

static t_vec3	get_base_color(t_world_translated world, t_mesh *mesh)
{
	t_vec2	uv;
	t_vec3	tex;

	if (!mesh->material.has_texture)
		return (mesh->material.color);
	if (world.has_uv)
		uv = world.uv;
	else
		uv = get_mesh_uv(mesh, world.point_local,
				world.geometric_normal_local);
	tex = sample_texture(&mesh->material.texture, uv);
	return (vec3_mul_vec3(tex, mesh->material.color));
}

static t_vec3	shade_one_light(t_shade_light_params lp)
{
	t_blimm_phong_params	bp;

	bp.mat = lp.curr_mesh->material;
	bp.mat.color = lp.base_color;
	bp.light_dir = vec3_normalize(
			vec3_sub(lp.light.position, lp.world.point));
	bp.dist = vec3_length(
			vec3_sub(lp.light.position, lp.world.point));
	bp.origin = vec3_add(lp.world.point,
			vec3_mul(lp.world.normal, EPSILON));
	bp.ray = ray_make(bp.origin, bp.light_dir,
			EPSILON, bp.dist);
	if (is_occluded(lp.scene, bp.ray, lp.curr_mesh))
		return (vec3_create(0, 0, 0));
	bp.diffuse = fmax(
			vec3_dot(lp.world.normal, bp.light_dir), 0.0f);
	if (bp.diffuse <= 0.0f)
		return (vec3_create(0, 0, 0));
	bp.half = vec3_normalize(
			vec3_add(bp.light_dir, lp.view_dir));
	bp.spec = powf(
			fmax(vec3_dot(lp.world.normal, bp.half), 0.0f),
			bp.mat.shininess);
	return (calc_color_hit_by_light(bp, lp.light));
}

t_vec3	shade_blinn_phong(t_world_translated world, t_vec3 view_dir,
		t_scene scene, t_mesh *curr_mesh)
{
	t_vec3					color;
	t_vec3					base_color;
	size_t					i;
	t_shade_light_params	lp;

	base_color = get_base_color(world, curr_mesh);
	color = vec3_mul(base_color, scene.ambient.intensity);
	lp.curr_mesh = curr_mesh;
	lp.base_color = base_color;
	lp.light = scene.light;
	lp.world = world;
	lp.view_dir = view_dir;
	lp.scene = scene;
	color = vec3_add(color,
			shade_one_light(lp));
	i = 0;
	while (i < scene.secondary_lights_qty)
	{
		lp.light = scene.secondary_lights[i];
		color = vec3_add(color, shade_one_light(lp));
		i++;
	}
	return (color);
}
