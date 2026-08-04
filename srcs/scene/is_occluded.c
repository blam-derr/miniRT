#include "scene.h"
#include "ray.h"
#include <math.h>
#define EPSILON 1e-6

char	is_any_triangle_intersected(t_vec3 ray_dir, t_vec3 ray_pos, t_triangle tri,
	float max_t)
{
	t_moller_trumbore_params	calc;

	calc.edge1 = vec3_sub(tri.v[1], tri.v[0]);
	calc.edge2 = vec3_sub(tri.v[2], tri.v[0]);
	calc.raydir_cross_edge2 = vec3_cross(ray_dir, calc.edge2);
	calc.det = vec3_dot(calc.edge1, calc.raydir_cross_edge2);
	if (fabsf(calc.det) < EPSILON)
		return (0);
	calc.inv_det = 1.0f / calc.det;
	calc.ray_length = vec3_sub(ray_pos, tri.v[0]);
	calc.bary_coords.u = vec3_dot(calc.ray_length, calc.raydir_cross_edge2) * calc.inv_det;
	if (calc.bary_coords.u < 0.0f || calc.bary_coords.u > 1.0f)
		return (0);
	calc.raylength_cross_edge1 = vec3_cross(calc.ray_length, calc.edge1);
	calc.bary_coords.v = vec3_dot(ray_dir, calc.raylength_cross_edge1) * calc.inv_det;
	if (calc.bary_coords.v < 0.0f || calc.bary_coords.u + calc.bary_coords.v > 1.0f)
		return (0);
	calc.ray_time = vec3_dot(calc.edge2, calc.raylength_cross_edge1) * calc.inv_det;
	if (calc.ray_time < EPSILON || calc.ray_time > max_t)
		return (0);
	return (1);
}

char	is_occluded(t_scene scene, t_vec3 origin, t_vec3 dir, float max_t, t_mesh *ignore_mesh)
{
	t_list	*objs;
	t_mesh	*mesh;
	t_vec3	world_up;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	local_pos;
	t_vec3	ray_pos_local;
	t_vec3	ray_dir_local;
	size_t	i;

	objs = scene.objects;
	while (objs)
	{
		mesh = (t_mesh *)objs->content;

		if (vec3_length(mesh->dir) < EPSILON)
			forward = vec3_create(0, 1, 0);
		else
			forward = vec3_normalize(mesh->dir);

		if (fabsf(forward.y) > 0.999f)
			world_up = vec3_create(1, 0, 0);
		else
			world_up = vec3_create(0, 1, 0);

		right = vec3_normalize(vec3_cross(world_up, forward));
		up = vec3_cross(forward, right);

		local_pos = vec3_sub(origin, mesh->pos);

		ray_pos_local.x = vec3_dot(local_pos, right);
		ray_pos_local.y = vec3_dot(local_pos, forward);
		ray_pos_local.z = vec3_dot(local_pos, up);

		ray_dir_local.x = vec3_dot(dir, right);
		ray_dir_local.y = vec3_dot(dir, forward);
		ray_dir_local.z = vec3_dot(dir, up);
		ray_dir_local = vec3_normalize(ray_dir_local);

		i = 0;
		if (mesh == ignore_mesh)
		{
			objs = objs->next;
			continue;
		}
		while (i < mesh->triangle_count)
		{
			if (is_any_triangle_intersected(
					ray_dir_local,
					ray_pos_local,
					mesh->triangles[i],
					max_t))
				return (1);
			i++;
		}
		objs = objs->next;
	}
	return (0);
}
