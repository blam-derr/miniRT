/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:08:38 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/16 19:23:07 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"
# include "vec.h"

typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER,
}				t_object_type;

typedef struct s_ambient
{
	float		intensity;
	t_vec3		color;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		direction;
	float		fov;
}				t_camera;

typedef struct s_light
{
	t_vec3		position;
	t_vec3		color;
	float		intensity;
}				t_light;

typedef struct s_sphere
{
	t_vec3		position;
	float		radius;
	t_vec3		color;
}				t_sphere;

typedef struct s_plane
{
	t_vec3		position;
	t_vec3		normal;
	t_vec3		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3		position;
	t_vec3		orientation;
	float		radius;
	float		height;
	t_vec3		color;
}				t_cylinder;

typedef struct s_generic_primitive
{
	int			type;
	union
	{
		t_plane		plane;
		t_cylinder	cylinder;
		t_sphere	sphere;
	}			u_data;
}				t_generic_primitive;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*objects;
}				t_scene;

void	free_whole_scene(t_scene *scene);

#endif
