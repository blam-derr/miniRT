/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:20:23 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/01 16:21:08 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec.h"

typedef struct s_hit
{
	float			t;
	unsigned int	color;
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
	float	rgb[3];
}	t_tri_params;

#endif
