/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:08:38 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/15 19:48:58 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"
# include "vec.h"

typedef struct s_ambient
{
	float		intensity;
	t_vec		color;
}				t_ambient;

typedef struct s_camera
{
	t_vec		position;
	t_vec		direction;
	float		fov;
}				t_camera;

typedef struct s_light
{
	t_vec		position;
	t_vec		color;
	float		intensity;
}				t_light;

typedef struct s_sphere
{
	t_vec		position;
	float		radius;
	t_vec		color;
}				t_sphere;

typedef struct s_plane
{
	t_vec		position;
	t_vec		normal;
	t_vec		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vec		position;
	t_vec		orientation;
	float		radius;
	float		height;
	t_vec		color;
}				t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*objects;
}				t_scene;

#endif
