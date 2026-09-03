/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:07:01 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/17 19:29:34 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H
# include "vec_bonus.h"

typedef struct s_hit	t_hit;
typedef struct s_scene	t_scene;
typedef struct s_mesh	t_mesh;
typedef struct s_ray	t_ray;

typedef struct s_triangle
{
	t_vec3	v[3];
	t_vec3	n[3];
}	t_triangle;

char	intersect_triangle(t_vec3 ray_dir, t_vec3 ray_pos, t_triangle tri,
			t_hit *hit);
char	is_any_triangle_intersected(t_vec3 ray_dir, t_vec3 ray_pos,
			t_triangle tri, float max_t);
char	is_occluded(t_scene scene, t_ray ray, t_mesh *ignore_mesh);

#endif
