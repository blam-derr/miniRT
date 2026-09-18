/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sample_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/17 20:35:01 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_bonus.h"
#include "vec_bonus.h"
#include <stdint.h>
#define X 0
#define Y 1

static int	wrap_texel(float coord, int size)
{
	int	index;

	index = (int)(coord * size);
	if (index >= size)
		index = size - 1;
	if (index < 0)
		index = 0;
	return (index);
}

t_vec3	sample_texture(t_texture *texture, t_vec2 uv)
{
	int			p[2];
	int			bytes_per_pixel;
	int			offset;
	uint32_t	pixel;
	t_vec3		color;

	if (!texture || !texture->addr
		|| texture->width <= 0 || texture->height <= 0)
		return (vec3_create(1, 1, 1));
	p[X] = wrap_texel(uv.u, texture->width);
	p[Y] = wrap_texel(uv.v, texture->height);
	bytes_per_pixel = texture->bpp / 8;
	if (bytes_per_pixel <= 0)
		bytes_per_pixel = 4;
	offset = p[Y] * texture->line_length + p[X] * bytes_per_pixel;
	ft_memcpy(&pixel, texture->addr + offset, sizeof(pixel));
	color.x = (float)((pixel >> 16) & 0xFF) / 255.0f;
	color.y = (float)((pixel >> 8) & 0xFF) / 255.0f;
	color.z = (float)(pixel & 0xFF) / 255.0f;
	return (color);
}
