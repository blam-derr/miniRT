/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:54:15 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/22 21:05:46 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

t_vec3	vec3_div(t_vec3 v, float s)
{
	t_vec3	res;

	res.x = v.x / s;
	res.y = v.y / s;
	res.z = v.z / s;
	return (res);
}

t_vec3	vec3_mul(t_vec3 v, float s)
{
	t_vec3	res;

	res.x = v.x * s;
	res.y = v.y * s;
	res.z = v.z * s;
	return (res);
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	float	res;

	res = a.x * b.x + a.y * b.y + a.z * b.z;
	return (res);
}

float	vec3_length(t_vec3 v)
{
	float	res;

	res = sqrtf(vec3_dot(v, v));
	return (res);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	t_vec3	res;
	float	len;

	len = vec3_length(v);
	res.x = 0;
	res.y = 0;
	res.z = 0;
	if (len == 0.0f)
		return (res);
	return (vec3_div(v, len));
}
