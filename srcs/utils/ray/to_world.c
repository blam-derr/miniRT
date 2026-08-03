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

#include "ray.h"
#include "vec.h"

t_vec3	local_to_world_point(t_vec3 point, t_hit *hit)
{
	t_vec3	world_pos;

	world_pos.x = (point.x * hit->basis_right.x)
		+ (point.y * hit->basis_up.x)
		+ (point.z * hit->basis_forward.x);
	world_pos.y = (point.x * hit->basis_right.y)
		+ (point.y * hit->basis_up.y)
		+ (point.z * hit->basis_forward.y);
	world_pos.z = (point.x * hit->basis_right.z)
		+ (point.y * hit->basis_up.z)
		+ (point.z * hit->basis_forward.z);
	return (world_pos);
}

t_vec3	local_to_world_normal(t_vec3 normal, t_hit *hit)
{
	t_vec3	world_normal;

	world_normal.x = (normal.x * hit->basis_right.x)
		+ (normal.y * hit->basis_up.x)
		+ (normal.z * hit->basis_forward.x);
	world_normal.y = (normal.x * hit->basis_right.y)
		+ (normal.y * hit->basis_up.y)
		+ (normal.z * hit->basis_forward.y);
	world_normal.z = (normal.x * hit->basis_right.z)
		+ (normal.y * hit->basis_up.z)
		+ (normal.z * hit->basis_forward.z);
	return (world_normal);
}
