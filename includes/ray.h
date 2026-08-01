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

# include "vec.h"
# include "mesh.h"

typedef struct s_hit
{
	float	ray_time;
	t_vec3	point_local;
	t_vec3	normal_local;
	t_mesh	*mesh;
	t_vec3	basis_right;
	t_vec3	basis_forward;
	t_vec3	basis_up;
	char	hit_something;
}	t_hit;

typedef struct s_tri_params
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	pvec;
	t_vec3	tvec;
	t_vec3	qvec;
	float	det;
	float	inv_det;
	float	u;
	float	v;
	float	t;
	t_vec3	normal;
}	t_tri_params;

t_vec3	local_to_world_normal(t_vec3 normal, t_hit *hit);
t_vec3	local_to_world_point(t_vec3 point, t_hit *hit);

#endif
