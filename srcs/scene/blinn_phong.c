#include "mesh.h"
#include "scene.h"
#include "vec.h"
#include <math.h>
#define EPSILON 1e-6

// TODO: NORMALIZE THE COLOR ON THE PARSER BETWEEN 0.0 and 0.1
t_vec3 shade_blinn_phong(t_vec3 point, t_vec3 normal, t_vec3 view_dir,
                         t_material mat, t_scene scene, t_mesh *curr_mesh) {
  t_vec3 color_res;

  color_res = vec3_mul(mat.color, scene.ambient.intensity);
  t_vec3 light_dir = vec3_normalize(vec3_sub(scene.light.position, point));
  float dist = vec3_length(vec3_sub(scene.light.position, point));
  t_vec3 origin = vec3_add(point, vec3_mul(normal, EPSILON));
  if (is_occluded(scene, origin, light_dir, dist, curr_mesh))
     return (color_res);
  float diffuse = fmax(vec3_dot(normal, light_dir), 0);
  
  float spec = 0.0f;
  
  if (diffuse > 0.0f)
  {
      t_vec3 half = vec3_normalize(vec3_add(light_dir, view_dir));
      spec = powf(fmax(vec3_dot(normal, half), 0.0f), mat.shininess);
  }
  t_vec3 light_ci = vec3_mul(scene.light.color, scene.light.intensity);
  // diffuse
  color_res = vec3_add(color_res,
  	vec3_mul_vec3(mat.color, vec3_mul(light_ci, diffuse * mat.diffuse_coefficient)));
  color_res = vec3_add(color_res, vec3_mul(light_ci, spec * mat.specular_coefficient));
  return (color_res);
}
