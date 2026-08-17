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

#include "aabb.h"
#include "mesh.h"
#include "scene.h"
#include "vec.h"
#include <math.h>

static t_vec3	calc_color_hit_by_light(t_blimm_phong_params bp, t_scene scene)
{
	bp.light_ci = vec3_mul(scene.light.color, scene.light.intensity);
	bp.color_res = vec3_add(bp.color_res,
			vec3_mul_vec3(bp.mat.color, vec3_mul(bp.light_ci,
					bp.diffuse * bp.mat.diffuse_coefficient)));
	bp.color_res = vec3_add(bp.color_res, vec3_mul(bp.light_ci,
				bp.spec * bp.mat.specular_coefficient));
	return (bp.color_res);
}

t_vec3	shade_blinn_phong(t_world_translated world, t_vec3 view_dir,
		t_scene scene, t_mesh *curr_mesh)
{
	t_blimm_phong_params	bp;

	bp.mat = curr_mesh->material;
	bp.color_res = vec3_mul(bp.mat.color, scene.ambient.intensity);
	bp.light_dir = vec3_normalize(vec3_sub(scene.light.position, world.point));
	bp.dist = vec3_length(vec3_sub(scene.light.position, world.point));
	bp.origin = vec3_add(world.point, vec3_mul(world.normal, EPSILON));
	bp.ray = ray_make(bp.origin, bp.light_dir, EPSILON, bp.dist);
	if (is_occluded(scene, bp.ray, curr_mesh))
		return (bp.color_res);
	bp.color_res = vec3_mul(bp.mat.color, scene.ambient.intensity);
	bp.diffuse = fmax(vec3_dot(world.normal, bp.light_dir), 0);
	bp.spec = 0.0f;
	if (bp.diffuse > 0.0f)
	{
		bp.half = vec3_normalize(vec3_add(bp.light_dir, view_dir));
		bp.spec = powf(fmax(vec3_dot(world.normal, bp.half), 0.0f),
				bp.mat.shininess);
	}
	bp.color_res = calc_color_hit_by_light(bp, scene);
	return (bp.color_res);
}
