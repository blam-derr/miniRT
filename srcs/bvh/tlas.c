/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlas.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/04 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "libft.h"
#include "scene.h"
#include <stdlib.h>
#define EPSILON 1e-6f

typedef struct s_stack_item
{
	int		node;
	float	t_enter;
}	t_stack_item;

t_bvh	*build_blas(t_mesh *mesh);
void	intersect_blas(t_mesh *mesh, t_ray *ray, t_hit *hit);
int		any_hit_blas(t_mesh *mesh, t_ray *ray);

static void	push(t_stack_item *stack, int *sp, int node, float t)
{
	if (*sp >= BVH_STACK_SIZE)
		return ;
	stack[*sp].node = node;
	stack[*sp].t_enter = t;
	(*sp)++;
}

static t_ray	world_to_local_ray(t_ray *world, t_mesh *mesh)
{
	t_vec3	p;
	t_vec3	local_o;
	t_vec3	local_d;
	t_ray	local;

	p = vec3_sub(world->origin, mesh->pos);
	local_o.x = vec3_dot(p, mesh->basis_right);
	local_o.y = vec3_dot(p, mesh->basis_forward);
	local_o.z = vec3_dot(p, mesh->basis_up);
	local_d.x = vec3_dot(world->dir, mesh->basis_right);
	local_d.y = vec3_dot(world->dir, mesh->basis_forward);
	local_d.z = vec3_dot(world->dir, mesh->basis_up);
	local = ray_make(local_o, local_d, world->tmin, world->tmax);
	return (local);
}

static void	intersect_instance(t_instance *inst, t_ray *ray, t_hit *hit)
{
	t_ray	local;
	float	prev;

	local = world_to_local_ray(ray, inst->mesh);
	prev = hit->ray_time;
	intersect_blas(inst->mesh, &local, hit);
	if (hit->ray_time < prev)
	{
		hit->mesh = inst->mesh;
		hit->basis_right = inst->mesh->basis_right;
		hit->basis_forward = inst->mesh->basis_forward;
		hit->basis_up = inst->mesh->basis_up;
		ray->tmax = hit->ray_time;
	}
}

static int	any_hit_instance(t_instance *inst, t_ray *ray, t_mesh *ignore)
{
	t_ray	local;

	if (inst->mesh == ignore)
		return (0);
	local = world_to_local_ray(ray, inst->mesh);
	return (any_hit_blas(inst->mesh, &local));
}

static void	intersect_leaf_instances(t_accel *accel, t_bvh *tlas, int first,
		int count, t_ray *ray, t_hit *hit)
{
	int	i;
	int	idx;

	i = 0;
	while (i < count)
	{
		idx = tlas->prim_indices[first + i];
		intersect_instance(&accel->instances[idx], ray, hit);
		i++;
	}
}

static int	any_hit_leaf_instances(t_accel *accel, t_bvh *tlas, int first,
		int count, t_ray *ray, t_mesh *ignore)
{
	int	i;
	int	idx;

	i = 0;
	while (i < count)
	{
		idx = tlas->prim_indices[first + i];
		if (any_hit_instance(&accel->instances[idx], ray, ignore))
			return (1);
		i++;
	}
	return (0);
}

void	intersect_tlas(t_accel *accel, t_ray *ray, t_hit *hit)
{
	t_bvh			*tlas;
	t_stack_item	stack[BVH_STACK_SIZE];
	int				sp;
	t_bvh_node		*node;
	float			t_enter;
	int				cur;

	if (!accel || !accel->tlas.nodes)
		return ;
	tlas = &accel->tlas;
	sp = 0;
	push(stack, &sp, tlas->root, 0.0f);
	while (sp > 0)
	{
		sp--;
		cur = stack[sp].node;
		if (stack[sp].t_enter >= ray->tmax)
			continue ;
		node = &tlas->nodes[cur];
		if (node->is_leaf)
			intersect_leaf_instances(accel, tlas, node->first, node->count,
				ray, hit);
		else
		{
			if (node->left >= 0)
			{
				if (ray_aabb_intersect(ray, tlas->nodes[node->left].bounds,
						&t_enter))
					push(stack, &sp, node->left, t_enter);
			}
			if (node->right >= 0)
			{
				if (ray_aabb_intersect(ray, tlas->nodes[node->right].bounds,
						&t_enter))
					push(stack, &sp, node->right, t_enter);
			}
		}
	}
}

int	tlas_any_hit(t_accel *accel, t_ray *ray, t_mesh *ignore_mesh)
{
	t_bvh			*tlas;
	t_stack_item	stack[BVH_STACK_SIZE];
	int				sp;
	t_bvh_node		*node;
	float			t_enter;
	int				cur;

	if (!accel || !accel->tlas.nodes)
		return (0);
	tlas = &accel->tlas;
	sp = 0;
	push(stack, &sp, tlas->root, 0.0f);
	while (sp > 0)
	{
		sp--;
		cur = stack[sp].node;
		if (stack[sp].t_enter >= ray->tmax)
			continue ;
		node = &tlas->nodes[cur];
		if (node->is_leaf)
		{
			if (any_hit_leaf_instances(accel, tlas, node->first, node->count,
					ray, ignore_mesh))
				return (1);
		}
		else
		{
			if (node->left >= 0)
			{
				if (ray_aabb_intersect(ray, tlas->nodes[node->left].bounds,
						&t_enter))
					push(stack, &sp, node->left, t_enter);
			}
			if (node->right >= 0)
			{
				if (ray_aabb_intersect(ray, tlas->nodes[node->right].bounds,
						&t_enter))
					push(stack, &sp, node->right, t_enter);
			}
		}
	}
	return (0);
}

static int	count_objects(t_list *objs)
{
	int	n;

	n = 0;
	while (objs)
	{
		n++;
		objs = objs->next;
	}
	return (n);
}

static int	build_tlas_tree(t_accel *accel)
{
	t_bvh_prim	*prims;
	t_bvh		*built;
	int			i;

	prims = (t_bvh_prim *)malloc(sizeof(t_bvh_prim)
			* (size_t)accel->instance_count);
	if (!prims)
		return (0);
	i = 0;
	while (i < accel->instance_count)
	{
		prims[i].bounds = accel->instances[i].world_bounds;
		prims[i].centroid = aabb_centroid(prims[i].bounds);
		prims[i].index = i;
		i++;
	}
	built = bvh_build(prims, accel->instance_count);
	free(prims);
	if (!built)
		return (0);
	accel->tlas = *built;
	free(built);
	return (1);
}

int	build_scene_accel(t_scene *scene)
{
	t_list		*objs;
	t_mesh		*mesh;
	t_accel		*accel;
	int			n;
	int			i;

	n = count_objects(scene->objects);
	if (n <= 0)
	{
		scene->accel = NULL;
		return (1);
	}
	accel = (t_accel *)malloc(sizeof(t_accel));
	if (!accel)
		return (0);
	accel->instances = (t_instance *)malloc(sizeof(t_instance) * (size_t)n);
	if (!accel->instances)
	{
		free(accel);
		return (0);
	}
	accel->instance_count = n;
	accel->tlas.nodes = NULL;
	accel->tlas.prim_indices = NULL;
	accel->tlas.node_count = 0;
	accel->tlas.prim_count = 0;
	accel->tlas.root = 0;
	objs = scene->objects;
	i = 0;
	while (objs)
	{
		mesh = (t_mesh *)objs->content;
		mesh_bake_transform(mesh);
		mesh->blas = build_blas(mesh);
		if (!mesh->blas)
		{
			scene->accel = accel;
			free_scene_accel(scene);
			return (0);
		}
		accel->instances[i].mesh = mesh;
		accel->instances[i].world_bounds = mesh->world_bounds;
		i++;
		objs = objs->next;
	}
	if (!build_tlas_tree(accel))
	{
		scene->accel = accel;
		free_scene_accel(scene);
		return (0);
	}
	scene->accel = accel;
	return (1);
}

void	free_scene_accel(t_scene *scene)
{
	t_list	*objs;
	t_mesh	*mesh;

	if (!scene)
		return ;
	objs = scene->objects;
	while (objs)
	{
		mesh = (t_mesh *)objs->content;
		if (mesh && mesh->blas)
		{
			bvh_free(mesh->blas);
			mesh->blas = NULL;
		}
		objs = objs->next;
	}
	if (!scene->accel)
		return ;
	free(scene->accel->tlas.nodes);
	free(scene->accel->tlas.prim_indices);
	free(scene->accel->instances);
	free(scene->accel);
	scene->accel = NULL;
}
