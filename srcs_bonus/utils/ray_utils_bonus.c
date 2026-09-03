/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 20:56:49 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/31 21:27:10 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_bonus.h"
#include "vec_bonus.h"
#include "camera_bonus.h"
#include "miniRT_bonus.h"

t_vec3	local_to_world_point(t_vec3 point, t_hit *hit)
{
	t_vec3	world_pos;

	world_pos.x = point.x * hit->basis_right.x
		+ point.y * hit->basis_forward.x
		+ point.z * hit->basis_up.x;
	world_pos.y = point.x * hit->basis_right.y
		+ point.y * hit->basis_forward.y
		+ point.z * hit->basis_up.y;
	world_pos.z = point.x * hit->basis_right.z
		+ point.y * hit->basis_forward.z
		+ point.z * hit->basis_up.z;
	world_pos = vec3_add(world_pos, hit->mesh->pos);
	return (world_pos);
}

t_vec3	local_to_world_normal(t_vec3 normal, t_hit *hit)
{
	t_vec3	world_normal;

	world_normal.x = normal.x * hit->basis_right.x
		+ normal.y * hit->basis_forward.x
		+ normal.z * hit->basis_up.x;
	world_normal.y = normal.x * hit->basis_right.y
		+ normal.y * hit->basis_forward.y
		+ normal.z * hit->basis_up.y;
	world_normal.z = normal.x * hit->basis_right.z
		+ normal.y * hit->basis_forward.z
		+ normal.z * hit->basis_up.z;
	return (vec3_normalize(world_normal));
}

t_vec3	get_ray_dir(float x, float y, t_camera camera,
		t_program program)
{
	float	aspect;
	float	scale;
	t_vec3	ray;

	aspect = (float)program.window_width / (float)program.window_height;
	scale = tanf(camera.fov * 0.5f * (M_PI / 180.0f));
	ray = vec3_add(camera.forward, vec3_add(vec3_mul(camera.right, x * aspect
					* scale), vec3_mul(camera.up, y * scale)));
	return (vec3_normalize(ray));
}
