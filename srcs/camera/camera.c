/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 20:22:01 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/27 17:11:31 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vec.h"

double	range_map_cam_coord(double val, double min, double max)
{
	double	mapped_val;
	double	res;

	res = 0.0;
	mapped_val = (val - min) / (max - min);
	res = -1.0 + mapped_val * (1.0 - -1.0);
	return (res);
}

void	calc_local_cam_axis(t_camera *cam)
{
	t_vec3	world_up;

	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	cam->forward = vec3_normalize(cam->direction);
	cam->right = vec3_normalize(vec3_cross(cam->forward, world_up));
	cam->up = vec3_normalize(vec3_cross(cam->right, cam->forward));
}
