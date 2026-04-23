/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:07:01 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/22 21:05:07 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H
# include "vec.h"

typedef struct s_triangle
{
	t_vec3	v[3];
	t_vec3	n[3];
}	t_triangle;

#endif
