/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 19:48:53 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/09 19:15:13 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "triangle.h"
#include "vec.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

static void	compute_cylinder_faces(t_vec3 *p, t_cyl cyl, float i)
{
	float	theta0;
	float	theta1;
	float	cos_theta[2];
	float	sin_theta[2];

	theta0 = 2.0f * M_PI * (i / (float)cyl.slices);
	theta1 = 2.0f * M_PI * ((i + 1) / (float)cyl.slices);
	cos_theta[0] = cosf(theta0);
	sin_theta[0] = sinf(theta0);
	cos_theta[1] = cosf(theta1);
	sin_theta[1] = sinf(theta1);
	p[0] = vec3_create(cyl.radius * cos_theta[0], -cyl.height / 2,
			cyl.radius * sin_theta[0]);
	p[1] = vec3_create(cyl.radius * cos_theta[0], cyl.height / 2,
			cyl.radius * sin_theta[0]);
	p[2] = vec3_create(cyl.radius * cos_theta[1], cyl.height / 2,
			cyl.radius * sin_theta[1]);
	p[3] = vec3_create(cyl.radius * cos_theta[1], -cyl.height / 2,
			cyl.radius * sin_theta[1]);
}

static void	compute_cylinder_normals(t_vec3 *n, t_cyl cyl, float j)
{
	float	theta0;
	float	theta1;

	theta0 = 2.0f * M_PI * (j / (float)cyl.slices);
	theta1 = 2.0f * M_PI * ((j + 1) / (float)cyl.slices);
	n[0] = vec3_create(cosf(theta0), 0.0f, sinf(theta0));
	n[1] = vec3_create(cosf(theta0), 0.0f, sinf(theta0));
	n[2] = vec3_create(cosf(theta1), 0.0f, sinf(theta1));
	n[3] = vec3_create(cosf(theta1), 0.0f, sinf(theta1));
}

static void	fill_side_triangles(t_mesh *mesh, size_t *index, t_vec3 *p,
		t_vec3 *n)
{
	mesh->triangles[*index].v[0] = p[0];
	mesh->triangles[*index].v[1] = p[1];
	mesh->triangles[*index].v[2] = p[2];
	mesh->triangles[*index].n[0] = n[0];
	mesh->triangles[*index].n[1] = n[1];
	mesh->triangles[*index].n[2] = n[2];
	(*index)++;
	mesh->triangles[*index].v[0] = p[0];
	mesh->triangles[*index].v[1] = p[2];
	mesh->triangles[*index].v[2] = p[3];
	mesh->triangles[*index].n[0] = n[0];
	mesh->triangles[*index].n[1] = n[2];
	mesh->triangles[*index].n[2] = n[3];
	(*index)++;
}

static void	generate_side_faces(t_mesh *mesh, size_t *index, t_cyl cyl)
{
	int		i;
	t_vec3	p[4];
	t_vec3	n[4];

	i = 0;
	while (i < cyl.slices)
	{
		compute_cylinder_faces(p, cyl, (float)i);
		compute_cylinder_normals(n, cyl, (float)i);
		fill_side_triangles(mesh, index, p, n);
		i++;
	}
}

t_mesh	*generate_cylinder(int slices, float radius, float height)
{
	t_mesh	*mesh;
	t_cyl	cyl;
	size_t	index;

	cyl.slices = slices;
	cyl.radius = radius / 2;
	cyl.height = height;
	mesh = malloc(sizeof(t_mesh));
	if (!mesh)
		return (NULL);
	mesh->triangle_count = slices * 4;
	mesh->triangles = malloc(mesh->triangle_count * sizeof(t_triangle));
	if (!mesh->triangles)
		return (NULL);
	index = 0;
	generate_side_faces(mesh, &index, cyl);
	generate_cylinder_caps(mesh, &index, cyl);
	return (mesh);
}
