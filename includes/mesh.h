/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:06:51 by fbenini-          #+#    #+#             */
/*   Updated: 2026/06/15 17:29:54 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H
# include "triangle.h"
# include <stddef.h>

typedef struct s_mesh
{
	size_t			triangle_count;
	t_triangle		*triangles;
	unsigned int	base_color;
}	t_mesh;


t_mesh	generate_sphere(int stacks, int slices, float radius);

#endif
