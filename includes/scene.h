/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:08:38 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/15 12:08:43 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"
# include "vec.h"

typedef struct s_ambient
{
	float	intensity;
	t_vec	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec	position;
	t_vec	direction;
	float	fov;
}	t_camera;

typedef struct s_light
{
	t_vec	position;
	t_vec	color;
	float	intensity;
}	t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*objects;
}	t_scene;

#endif
