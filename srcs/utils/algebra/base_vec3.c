/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:51:20 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/27 16:55:41 by fbenini-         ###   ########.fr       */
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

float	vec3_length(t_vec3 v)
{
	float	res;

	res = sqrtf(vec3_dot(v, v));
	return (res);
}
