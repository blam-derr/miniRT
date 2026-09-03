/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by fbenini-          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "mesh_bonus.h"
# include <stddef.h>

typedef struct s_obj_data
{
	t_vec3		*verts;
	size_t		v_count;
	size_t		v_cap;
	t_vec3		*normals;
	size_t		n_count;
	size_t		n_cap;
	t_triangle	*tris;
	size_t		t_count;
	size_t		t_cap;
}	t_obj_data;

typedef struct s_face_idx
{
	size_t	*v;
	long	*n;
	int		count;
}	t_face_idx;

t_mesh	*parse_obj_file(char *filename);
int		push_vec3(t_vec3 **arr, size_t *count, size_t *cap, t_vec3 v);
int		push_triangle(t_obj_data *data, t_triangle tri);
int		parse_vec3_line(char **tokens, t_obj_data *data, int is_normal);
int		parse_face_line(char **tokens, t_obj_data *data);
int		parse_face_token(char *token, t_obj_data *data, size_t *v_idx,
			long *n_idx);
int		emit_triangle(t_obj_data *data, size_t *v, long *n);
void	set_tri_normals(t_obj_data *data, t_triangle *tri, long *n);

#endif
