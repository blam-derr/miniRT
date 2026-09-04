/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vec3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:41:51 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/04 20:45:47 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_bonus.h"

t_vec3	vec3_create(float x, float y, float z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}
