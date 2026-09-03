/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "aabb_bonus.h"
# include "mesh_bonus.h"
# include "ray_bonus.h"
# include "scene_bonus.h"

# define BVH_LEAF_MAX 8
# define BVH_STACK_SIZE 64

typedef struct s_bvh_node
{
	t_aabb	bounds;
	int		left;
	int		right;
	int		first;
	int		count;
	int		is_leaf;
}	t_bvh_node;

typedef struct s_bvh
{
	t_bvh_node	*nodes;
	int			*prim_indices;
	int			node_count;
	int			prim_count;
	int			root;
}	t_bvh;

typedef struct s_bvh_prim
{
	t_aabb	bounds;
	t_vec3	centroid;
	int		index;
}	t_bvh_prim;

typedef struct s_stack_item
{
	int		node;
	float	t_enter;
}	t_stack_item;

typedef struct s_bvh_traversal
{
	t_bvh			*bvh;
	t_stack_item	stack[BVH_STACK_SIZE];
	int				sp;
}	t_bvh_traversal;

typedef struct s_instance
{
	t_mesh	*mesh;
	t_aabb	world_bounds;
}	t_instance;

typedef struct s_accel
{
	t_instance	*instances;
	int			instance_count;
	t_bvh		tlas;
}	t_accel;

typedef struct s_build_ctx
{
	t_bvh_prim	*prims;
	t_bvh_node	*nodes;
	int			node_count;
	int			node_cap;
}	t_build_ctx;

void	mesh_bake_transform(t_mesh *mesh);
t_aabb	bounds_of_range(t_bvh_prim *prims, int first, int count);
t_aabb	centroid_bounds(t_bvh_prim *prims, int first, int count);
int		partition_mid(t_bvh_prim *prims, int first, int count, int axis);
t_bvh	*allocate_bvh(int prim_count);
void	fill_prim_indices(t_bvh *bvh, t_bvh_prim *prims, int count);
t_bvh	*bvh_build(t_bvh_prim *prims, int prim_count);
void	bvh_free(t_bvh *bvh);
t_bvh	*build_blas(t_mesh *mesh);
void	intersect_blas(t_mesh *mesh, t_ray *ray, t_hit *hit);
int		any_hit_blas(t_mesh *mesh, t_ray *ray);
t_ray	world_to_local_ray(t_ray *world, t_mesh *mesh);
void	bvh_push(t_bvh_traversal *tr, int node, float t);
void	bvh_traverse_children(t_bvh_traversal *tr, t_ray *ray,
			t_bvh_node *node);
int		build_scene_accel(t_scene *scene);
void	free_scene_accel(t_scene *scene);
void	intersect_tlas(t_accel *accel, t_ray *ray, t_hit *hit);
int		tlas_any_hit(t_accel *accel, t_ray *ray, t_mesh *ignore_mesh);

#endif
