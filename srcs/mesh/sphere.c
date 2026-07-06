/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:22:11 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/01 16:43:19 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "triangle.h"
#include "vec.h"
#include <math.h>
#include <stdlib.h>

static void	compute_faces(t_vec3 *p, t_sphere_face_data fd, int j)
{
	float	theta0;
	float	theta1;

	theta0 = 2.0f * M_PI * (j / fd.slices);
	theta1 = 2.0f * M_PI * ((j + 1) / fd.slices);
	p[0] = vec3_create(
			fd.radius * sinf(fd.phi0) * cosf(theta0),
			fd.radius * cosf(fd.phi0),
			fd.radius * sinf(fd.phi0) * sinf(theta0));
	p[1] = vec3_create(
			fd.radius * sinf(fd.phi1) * cosf(theta0),
			fd.radius * cosf(fd.phi1),
			fd.radius * sinf(fd.phi1) * sinf(theta0));
	p[2] = vec3_create(
			fd.radius * sinf(fd.phi1) * cosf(theta1),
			fd.radius * cosf(fd.phi1),
			fd.radius * sinf(fd.phi1) * sinf(theta1));
	p[3] = vec3_create(
			fd.radius * sinf(fd.phi0) * cosf(theta1),
			fd.radius * cosf(fd.phi0),
			fd.radius * sinf(fd.phi0) * sinf(theta1));
}

static void	compute_normals(t_vec3 *n, t_vec3 *p, float radius)
{
	n[0] = vec3_create(p[0].x / radius, p[0].y / radius, p[0].z / radius);
	n[1] = vec3_create(p[1].x / radius, p[1].y / radius, p[1].z / radius);
	n[2] = vec3_create(p[2].x / radius, p[2].y / radius, p[2].z / radius);
	n[3] = vec3_create(p[3].x / radius, p[3].y / radius, p[3].z / radius);
}

static void	process_face(t_sphere_work *w, int i, int j)
{
	t_vec3				p[4];
	t_vec3				n[4];
	t_sphere_face_data	fd;

	fd.phi0 = M_PI * ((float)i / w->stacks);
	fd.phi1 = M_PI * ((float)(i + 1) / w->stacks);
	fd.radius = w->radius;
	fd.slices = w->slices;
	compute_faces(p, fd, j);
	compute_normals(n, p, w->radius);
	w->res->triangles[w->index].v[0] = p[0];
	w->res->triangles[w->index].v[1] = p[1];
	w->res->triangles[w->index].v[2] = p[2];
	w->res->triangles[w->index].n[0] = n[0];
	w->res->triangles[w->index].n[1] = n[1];
	w->res->triangles[w->index].n[2] = n[2];
	w->index++;
	w->res->triangles[w->index].v[0] = p[0];
	w->res->triangles[w->index].v[1] = p[2];
	w->res->triangles[w->index].v[2] = p[3];
	w->res->triangles[w->index].n[0] = n[0];
	w->res->triangles[w->index].n[1] = n[2];
	w->res->triangles[w->index].n[2] = n[3];
	w->index++;
}

t_mesh	*generate_sphere(int stacks, int slices, float radius)
{
	t_mesh			*res;
	t_sphere_work	w;
	int				i;
	int				j;

	res = malloc(sizeof(t_mesh));
	res->triangle_count = stacks * slices * 2;
	res->triangles = malloc(sizeof(t_triangle) * res->triangle_count);
	w.res = res;
	w.radius = radius / 2;
	w.slices = slices;
	w.stacks = stacks;
	w.index = 0;
	i = 0;
	while (i < stacks)
	{
		j = 0;
		while (j < slices)
		{
			process_face(&w, i, j);
			j++;
		}
		i++;
	}
	return (res);
}
