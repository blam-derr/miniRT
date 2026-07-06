/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 19:48:50 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/06 20:11:35 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "triangle.h"
#include "vec.h"
#include <stdlib.h>

static void	calc_first_triangle(t_triangle *triangle)
{
	t_vec3	n;

	n.x = 0;
	n.y = 1;
	n.z = 0;
	triangle->v[0].x = -100;
	triangle->v[0].y = 0;
	triangle->v[0].z = -100;
	triangle->v[1].x = -100;
	triangle->v[1].y = 0;
	triangle->v[1].z = 100;
	triangle->v[2].x = 100;
	triangle->v[2].y = 0;
	triangle->v[2].z = -100;
	triangle->n[0] = n;
	triangle->n[1] = n;
	triangle->n[2] = n;
}

static void	calc_second_triangle(t_triangle *triangle)
{
	t_vec3	n;

	n.x = 0;
	n.y = 1;
	n.z = 0;
	triangle->v[0].x = 100;
	triangle->v[0].y = 0;
	triangle->v[0].z = 100;
	triangle->v[1].x = -100;
	triangle->v[1].y = 0;
	triangle->v[1].z = 100;
	triangle->v[2].x = 100;
	triangle->v[2].y = 0;
	triangle->v[2].z = -100;
	triangle->n[0] = n;
	triangle->n[1] = n;
	triangle->n[2] = n;
}

t_mesh	*generate_plane(void)
{
	t_mesh	*mesh;

	mesh = malloc(sizeof(t_mesh));
	mesh->triangle_count = 2;
	mesh->triangles = malloc(mesh->triangle_count * sizeof(t_triangle));
	calc_first_triangle(&mesh->triangles[0]);
	calc_second_triangle(&mesh->triangles[1]);
	return (mesh);
}
