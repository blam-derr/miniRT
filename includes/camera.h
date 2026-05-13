/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:08:28 by fbenini-          #+#    #+#             */
/*   Updated: 2026/05/12 20:18:38 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vec.h"

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
