/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:08:14 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/31 21:14:52 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

t_vec3	vec3_create(float x, float y, float z);

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_div(t_vec3 v, float s);
t_vec3	vec3_mul(t_vec3 v, float s);
float	vec3_length(t_vec3 v);

t_vec3	vec3_normalize(t_vec3 v);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_add_by_scalar(t_vec3 a, float s);
t_vec3	vec3_mul_vec3(t_vec3 a, t_vec3 b);

#endif
