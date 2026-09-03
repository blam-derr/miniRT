/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:20:23 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/31 21:11:32 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "mesh_bonus.h"
# include "vec_bonus.h"
# include <math.h>
# include <stddef.h>
# include <stdio.h>

typedef struct s_hit
{
	float			ray_time;
	t_vec3			point_local;
	t_vec3			normal_local;
	t_mesh			*mesh;
	t_vec3			basis_right;
	t_vec3			basis_forward;
	t_vec3			basis_up;
	char			hit_something;
}					t_hit;

typedef struct s_barycenter
{
	float			u;
	float			v;
}					t_barycenter;

typedef struct s_moller_trumbore_params
{
	t_vec3			edge1;
	t_vec3			edge2;
	t_vec3			raydir_cross_edge2;
	t_vec3			ray_length;
	t_vec3			raylength_cross_edge1;
	float			det;
	float			inv_det;
	t_barycenter	bary_coords;
	float			ray_time;
}					t_moller_trumbore_params;

t_vec3				local_to_world_normal(t_vec3 normal, t_hit *hit);
t_vec3				local_to_world_point(t_vec3 point, t_hit *hit);

#endif
