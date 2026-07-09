/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:06:51 by fbenini-          #+#    #+#             */
/*   Updated: 2026/07/01 16:40:57 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H
# include "triangle.h"
# include "vec.h"
# include <stddef.h>

typedef struct s_mesh
{
	size_t			triangle_count;
	t_triangle		*triangles;
	unsigned int	base_color;
	t_vec3			pos;
	t_vec3			dir;
}					t_mesh;

typedef struct s_sphere_face_data
{
	float	phi0;
	float	phi1;
	float	radius;
	float	slices;
}	t_sphere_face_data;

typedef struct s_sphere_work
{
	t_mesh	*res;
	float	radius;
	int		slices;
	int		stacks;
	int		index;
}	t_sphere_work;

typedef struct s_cyl
{
	int		slices;
	float	radius;
	float	height;
}	t_cyl;

void	generate_cylinder_caps(t_mesh *mesh, size_t *index, t_cyl cyl);

t_mesh	*generate_sphere(int stacks, int slices, float radius);
t_mesh	*generate_plane(void);
t_mesh	*generate_cylinder(int slices, float radius, float height);

#endif
