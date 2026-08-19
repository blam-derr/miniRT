/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/19 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <stdlib.h>

t_bvh	*allocate_bvh(int prim_count)
{
	t_bvh	*bvh;

	bvh = (t_bvh *)malloc(sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->prim_indices = (int *)malloc(sizeof(int) * (size_t)prim_count);
	if (!bvh->prim_indices)
	{
		free(bvh);
		return (NULL);
	}
	bvh->nodes = (t_bvh_node *)malloc(sizeof(t_bvh_node)
			* (size_t)(prim_count * 2));
	if (!bvh->nodes)
	{
		free(bvh->prim_indices);
		free(bvh);
		return (NULL);
	}
	return (bvh);
}

void	fill_prim_indices(t_bvh *bvh, t_bvh_prim *prims, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		bvh->prim_indices[i] = prims[i].index;
		i++;
	}
}

void	bvh_free(t_bvh *bvh)
{
	if (!bvh)
		return ;
	free(bvh->nodes);
	free(bvh->prim_indices);
	free(bvh);
}
