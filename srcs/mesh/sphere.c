/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:22:11 by fbenini-          #+#    #+#             */
/*   Updated: 2026/06/15 19:00:05 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "triangle.h"
#include "vec.h"
#include <math.h>
#include <stdlib.h>

t_vec3	vec3_create(float x, float y, float z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

static void	compute_faces(t_vec3 *p,
							float phi0,
							float phi1,
							float radius,
							float slices,
							float j)
{
	float	theta0;
	float	theta1;
	float	cosf_theta[2];
	float	sinf_theta[2];
	float	cosf_phi[2];
	float	sinf_phi[2];

	theta0 = 2.0f * M_PI * (j / slices);
	theta1 = 2.0f * M_PI * ((j + 1) / slices);
	cosf_theta[0] = cosf(theta0);
	sinf_theta[0] = sinf(theta0);
	cosf_theta[1] = cosf(theta1);
	sinf_theta[1] = sinf(theta1);
	cosf_phi[0] = cosf(phi0);
	cosf_phi[1] = cosf(phi1);
	sinf_phi[0] = sinf(phi0);
	sinf_phi[1] = sinf(phi1);
	p[0] = vec3_create(
		radius * sinf_phi[0] * cosf_theta[0],
		radius * cosf_phi[0],
		radius * sinf_phi[0] * sinf_theta[0]
	);
	p[1] = vec3_create(
		radius * sinf_phi[1] * cosf_theta[0],
		radius * cosf_phi[1],
		radius * sinf_phi[1] * sinf_theta[0]
	);
	p[2] = vec3_create(
		radius * sinf_phi[1] * cosf_theta[1],
		radius * cosf_phi[1],
		radius * sinf_phi[1] * sinf_theta[1]
	);
	p[3] = vec3_create(
		radius * sinf_phi[0] * cosf_theta[1],
		radius * cosf_phi[0],
		radius * sinf_phi[0] * sinf_theta[1]
	);
}

static void	compute_normals(t_vec3 *n, t_vec3 *p, float radius)
{
	n[0] = vec3_create(p[0].x / radius, p[0].y / radius, p[0].z / radius);
	n[1] = vec3_create(p[1].x / radius, p[1].y / radius, p[1].z / radius);
	n[2] = vec3_create(p[2].x / radius, p[2].y / radius, p[2].z / radius);
	n[3] = vec3_create(p[3].x / radius, p[3].y / radius, p[3].z / radius);
}

t_triangle	create_triangle(t_vec3 p0, t_vec3 p1, t_vec3 p2, t_vec3 n0, t_vec3 n1, t_vec3 n2)
{
	t_triangle	res;

	res.v[0] = p0;
	res.v[1] = p1;
	res.v[2] = p2;
	res.n[0] = n0;
	res.n[1] = n1;
	res.n[2] = n2;
	return (res);
}

t_mesh	generate_sphere(int stacks, int slices, float radius)
{
	t_mesh	res;
	t_vec3	p[4];
	t_vec3	n[4];

	res.triangle_count = stacks * slices * 2;
	res.triangles = malloc(sizeof(t_triangle) * res.triangle_count);
	int index = 0;

	for (int i = 0; i < stacks; i++)
	{
		float phi0 = M_PI * ((float)i / stacks);
		float phi1 = M_PI * ((float)(i + 1) / stacks);
		for (int j = 0; j < slices; j++)
		{
			compute_faces(p, phi0, phi1, radius, slices, j);
			compute_normals(n, p, radius);
			res.triangles[index++] = create_triangle(p[0], p[1], p[2], n[0], n[1], n[2]);
			res.triangles[index++] = create_triangle(p[0], p[2], p[3], n[0], n[2], n[3]);
		}
	}
	return (res);
}
