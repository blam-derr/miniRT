/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blas_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <stdlib.h>

t_bvh	*build_blas(t_mesh *mesh)
{
	t_bvh_prim	*prims;
	t_bvh		*bvh;
	size_t		i;
	t_aabb		box;

	if (!mesh || mesh->triangle_count == 0)
		return (NULL);
	prims = (t_bvh_prim *)malloc(sizeof(t_bvh_prim) * mesh->triangle_count);
	if (!prims)
		return (NULL);
	i = 0;
	while (i < mesh->triangle_count)
	{
		box = aabb_empty();
		aabb_expand_point(&box, mesh->triangles[i].v[0]);
		aabb_expand_point(&box, mesh->triangles[i].v[1]);
		aabb_expand_point(&box, mesh->triangles[i].v[2]);
		prims[i].bounds = box;
		prims[i].centroid = aabb_centroid(box);
		prims[i].index = (int)i;
		i++;
	}
	bvh = bvh_build(prims, (int)mesh->triangle_count);
	free(prims);
	return (bvh);
}
