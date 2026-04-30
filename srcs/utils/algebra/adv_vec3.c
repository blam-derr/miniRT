/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_vec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:53:27 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/27 17:05:57 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	float	res;

	res = a.x * b.x + a.y * b.y + a.z * b.z;
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

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}
