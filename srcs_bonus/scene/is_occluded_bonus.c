/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_occluded.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/17 18:46:53 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"
#include "scene_bonus.h"

char	is_occluded(t_scene scene, t_ray ray, t_mesh *ignore_mesh)
{
	if (!scene.accel)
		return (0);
	return ((char)tlas_any_hit(scene.accel, &ray, ignore_mesh));
}
