/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:12:59 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/09 19:13:39 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "triangle.h"
#include "vec.h"
#include <math.h>

static void	compute_cap_points(t_vec3 *p, t_cyl cyl, float j)
{
	float	theta0;
	float	theta1;
	float	half_h;

	half_h = cyl.height / 2.0f;
	theta0 = 2.0f * M_PI * (j / (float)cyl.slices);
	theta1 = 2.0f * M_PI * ((j + 1) / (float)cyl.slices);
	p[0] = vec3_create(cyl.radius * cosf(theta0), half_h,
			cyl.radius * sinf(theta0));
	p[1] = vec3_create(cyl.radius * cosf(theta1), half_h,
			cyl.radius * sinf(theta1));
	p[2] = vec3_create(cyl.radius * cosf(theta0), -half_h,
			cyl.radius * sinf(theta0));
	p[3] = vec3_create(cyl.radius * cosf(theta1), -half_h,
			cyl.radius * sinf(theta1));
}

static void	fill_cap_triangle(t_triangle *tri, t_vec3 center, t_vec3 normal,
		t_vec3 *v)
{
	tri->v[0] = center;
	tri->v[1] = v[0];
	tri->v[2] = v[1];
	tri->n[0] = normal;
	tri->n[1] = normal;
	tri->n[2] = normal;
}

static void	add_cap_pair(t_mesh *mesh, size_t *index, t_cyl cyl, float j)
{
	t_vec3	p[4];
	t_vec3	top[2];
	t_vec3	bottom[2];

	compute_cap_points(p, cyl, j);
	top[0] = p[0];
	top[1] = p[1];
	bottom[0] = p[3];
	bottom[1] = p[2];
	fill_cap_triangle(&mesh->triangles[*index], vec3_create(0.0f,
			cyl.height / 2.0f, 0.0f), vec3_create(0.0f, 1.0f, 0.0f), top);
	(*index)++;
	fill_cap_triangle(&mesh->triangles[*index], vec3_create(0.0f,
			-cyl.height / 2.0f, 0.0f), vec3_create(0.0f, -1.0f, 0.0f),
		bottom);
	(*index)++;
}

void	generate_cylinder_caps(t_mesh *mesh, size_t *index, t_cyl cyl)
{
	int	j;

	j = 0;
	while (j < cyl.slices)
	{
		add_cap_pair(mesh, index, cyl, (float)j);
		j++;
	}
}
