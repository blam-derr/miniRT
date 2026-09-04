/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:08:28 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:49:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_BONUS_H
# define CAMERA_BONUS_H

# include "vec_bonus.h"

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		direction;
	t_vec3		forward;
	t_vec3		up;
	t_vec3		right;
	float		fov;
}				t_camera;

double	range_map_cam_coord(double val, double min, double max);
void	calc_local_cam_axis(t_camera *cam);

#endif
