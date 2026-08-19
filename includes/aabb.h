/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/18 15:40:18 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

# include "vec.h"

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}	t_aabb;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
	t_vec3	inv_dir;
	float	tmin;
	float	tmax;
}	t_ray;

typedef struct s_local_dirs
{
	t_vec3	right;
	t_vec3	forward;
	t_vec3	up;
}	t_local_dirs;

t_aabb	aabb_empty(void);
t_aabb	aabb_from_point(t_vec3 p);
void	aabb_expand_point(t_aabb *box, t_vec3 p);
void	aabb_expand_aabb(t_aabb *box, t_aabb other);
t_vec3	aabb_centroid(t_aabb box);
float	aabb_surface_area(t_aabb box);
int		aabb_longest_axis(t_aabb box);
t_aabb	aabb_transform(t_aabb local, t_vec3 pos, t_local_dirs dirs);

t_ray	ray_make(t_vec3 origin, t_vec3 dir, float tmin, float tmax);
int		ray_aabb_intersect(const t_ray *ray, t_aabb box, float *t_enter);

#endif
