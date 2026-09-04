/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blinn_phong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:41:08 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/17 19:40:44 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb_bonus.h"
#include "mesh_bonus.h"
#include "scene_bonus.h"
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

static t_vec3	shade_one_light(t_world_translated world,
		t_vec3 view_dir, t_scene scene, t_mesh *curr_mesh, t_light light)
{
	t_blimm_phong_params	bp;
	t_vec3					result;

	bp.mat = curr_mesh->material;
	bp.light_dir = vec3_normalize(
			vec3_sub(light.position, world.point));
	bp.dist = vec3_length(
			vec3_sub(light.position, world.point));
	bp.origin = vec3_add(world.point,
			vec3_mul(world.normal, EPSILON));
	bp.ray = ray_make(bp.origin, bp.light_dir,
			EPSILON, bp.dist);
	if (is_occluded(scene, bp.ray, curr_mesh))
		return (vec3_create(0, 0, 0));
	bp.diffuse = fmax(
			vec3_dot(world.normal, bp.light_dir), 0.0f);
	if (bp.diffuse <= 0.0f)
		return (vec3_create(0, 0, 0));
	bp.half = vec3_normalize(
			vec3_add(bp.light_dir, view_dir));
	bp.spec = powf(
			fmax(vec3_dot(world.normal, bp.half), 0.0f),
			bp.mat.shininess);
	result = calc_color_hit_by_light(bp, light);
	return (result);
}

t_vec3	shade_blinn_phong(t_world_translated world, t_vec3 view_dir,
		t_scene scene, t_mesh *curr_mesh)
{
	t_vec3	color;
	size_t	i;

	color = vec3_mul(curr_mesh->material.color,
			scene.ambient.intensity);
	color = vec3_add(color,
			shade_one_light(world, view_dir, scene,
				curr_mesh, scene.light));
	i = 0;
	while (i < scene.secondary_lights_qty)
	{
		color = vec3_add(color,
				shade_one_light(world, view_dir, scene,
					curr_mesh, scene.secondary_lights[i]));
		i++;
	}
	return (color);
}
