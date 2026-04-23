/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:53:48 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/22 20:59:20 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "vec.h"
#include "algebra.h"

static int	clamp_color(float c)
{
	if (c < 0.0f)
		return (0);
	if (c > 255.0f)
		return (255);
	return ((int)c);
}

uint32_t	vec_to_hex(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = clamp_color(color.x);
	g = clamp_color(color.y);
	b = clamp_color(color.z);
	return ((r << 16) | (g << 8) | b);
}

t_vec3	apply_color_intensity(float intensity, t_vec3 color)
{
	t_vec3	res;

	res = vec3_mul(color, intensity);
	return (res);
}
