NAME = miniRT

NAME_BONUS = miniRT_bonus

CC = cc

CFLAGS = -Wextra -Wall -Werror -O3 -march=native

MINILIB = ./libs/minilibx/libmlx_Linux.a

MINILIB_DIR = ./libs/minilibx

MINILIB_HDR = ./libs/minilibx/mlx.h

LIBFT = ./libs/libft/libft.a

LIBFT_DIR = ./libs/libft

LIBFT_HDR = ./libs/libft/libft.h

INC = ./includes

INC_BONUS = ./includes_bonus

SRCS =	./srcs/main.c \
		./srcs/hooks.c \
		./srcs/camera/camera.c \
		./srcs/utils/ft_atof.c \
		./srcs/utils/arrays/int_array_utils.c \
		./srcs/utils/arrays/string_array_utils.c \
		./srcs/utils/arrays/ft_split_charset.c \
		./srcs/utils/string/is_whitespace.c \
		./srcs/utils/draw/put_pixel.c \
		./srcs/utils/draw/color.c \
		./srcs/utils/algebra/base_vec3.c \
		./srcs/utils/algebra/adv_vec3.c \
		./srcs/utils/algebra/create_vec3.c \
		./srcs/utils/ray_utils.c \
		./srcs/parser/parser.c \
		./srcs/parser/file_validation.c \
		./srcs/parser/dispatcher/dispatcher.c \
		./srcs/parser/dispatcher/parse_required.c \
		./srcs/parser/dispatcher/parse_objects.c \
		./srcs/parser/obj/obj_arrays.c \
		./srcs/parser/obj/obj_face.c \
		./srcs/parser/obj/obj_face_line.c \
		./srcs/parser/obj/obj_parser.c \
		./srcs/parser/obj/obj_vertex.c \
		./srcs/parser/obj/parse_obj.c \
		./srcs/scene/cleanup.c \
		./srcs/scene/ray.c \
		./srcs/scene/is_occluded.c \
		./srcs/scene/blinn_phong.c \
		./srcs/scene/triangle_intersection.c \
		./srcs/mesh/sphere.c \
		./srcs/mesh/plane.c \
		./srcs/mesh/cylinder.c \
		./srcs/mesh/cylinder_caps.c \
		./srcs/bvh/aabb.c \
		./srcs/bvh/aabb_metrics.c \
		./srcs/bvh/aabb_ray.c \
		./srcs/bvh/mesh_bake.c \
		./srcs/bvh/median_build.c \
		./srcs/bvh/bvh_build.c \
		./srcs/bvh/bvh_alloc.c \
		./srcs/bvh/bvh_traverse.c \
		./srcs/bvh/blas.c \
		./srcs/bvh/blas_build.c \
		./srcs/bvh/tlas.c \
		./srcs/bvh/tlas_any.c \
		./srcs/bvh/tlas_build.c \
		./srcs/bvh/tlas_free.c

SRCS_BONUS =	./srcs_bonus/main_bonus.c \
		./srcs_bonus/hooks_bonus.c \
		./srcs_bonus/camera/camera_bonus.c \
		./srcs_bonus/utils/ft_atof_bonus.c \
		./srcs_bonus/utils/arrays/int_array_utils_bonus.c \
		./srcs_bonus/utils/arrays/string_array_utils_bonus.c \
		./srcs_bonus/utils/arrays/ft_split_charset_bonus.c \
		./srcs_bonus/utils/string/is_whitespace_bonus.c \
		./srcs_bonus/utils/draw/put_pixel_bonus.c \
		./srcs_bonus/utils/draw/color_bonus.c \
		./srcs_bonus/utils/algebra/base_vec3_bonus.c \
		./srcs_bonus/utils/algebra/adv_vec3_bonus.c \
		./srcs_bonus/utils/algebra/create_vec3_bonus.c \
		./srcs_bonus/utils/ray_utils_bonus.c \
		./srcs_bonus/parser/parser_bonus.c \
		./srcs_bonus/parser/file_validation_bonus.c \
		./srcs_bonus/parser/dispatcher/dispatcher_bonus.c \
		./srcs_bonus/parser/dispatcher/parse_required_bonus.c \
		./srcs_bonus/parser/dispatcher/parse_objects_bonus.c \
		./srcs_bonus/parser/obj/obj_arrays_bonus.c \
		./srcs_bonus/parser/obj/obj_face_bonus.c \
		./srcs_bonus/parser/obj/obj_face_line_bonus.c \
		./srcs_bonus/parser/obj/obj_parser_bonus.c \
		./srcs_bonus/parser/obj/obj_vertex_bonus.c \
		./srcs_bonus/parser/obj/parse_obj_bonus.c \
		./srcs_bonus/scene/cleanup_bonus.c \
		./srcs_bonus/scene/ray_bonus.c \
		./srcs_bonus/scene/is_occluded_bonus.c \
		./srcs_bonus/scene/blinn_phong_bonus.c \
		./srcs_bonus/scene/triangle_intersection_bonus.c \
		./srcs_bonus/mesh/sphere_bonus.c \
		./srcs_bonus/mesh/plane_bonus.c \
		./srcs_bonus/mesh/cylinder_bonus.c \
		./srcs_bonus/mesh/cylinder_caps_bonus.c \
		./srcs_bonus/bvh/aabb_bonus.c \
		./srcs_bonus/bvh/aabb_metrics_bonus.c \
		./srcs_bonus/bvh/aabb_ray_bonus.c \
		./srcs_bonus/bvh/mesh_bake_bonus.c \
		./srcs_bonus/bvh/median_build_bonus.c \
		./srcs_bonus/bvh/bvh_build_bonus.c \
		./srcs_bonus/bvh/bvh_alloc_bonus.c \
		./srcs_bonus/bvh/bvh_traverse_bonus.c \
		./srcs_bonus/bvh/blas_bonus.c \
		./srcs_bonus/bvh/blas_build_bonus.c \
		./srcs_bonus/bvh/tlas_bonus.c \
		./srcs_bonus/bvh/tlas_any_bonus.c \
		./srcs_bonus/bvh/tlas_build_bonus.c \
		./srcs_bonus/bvh/tlas_free_bonus.c


OBJS = $(patsubst ./srcs/%.c,./objs/%.o,$(SRCS))

OBJS_BONUS = $(patsubst ./srcs_bonus/%.c,./objs_bonus/%.o,$(SRCS_BONUS))

$(NAME): $(OBJS) $(MINILIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MINILIB_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lXext -lX11 -lm -lz -lft

$(NAME_BONUS): $(OBJS_BONUS) $(MINILIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS) -L$(MINILIB_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lXext -lX11 -lm -lz -lft

objs/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -I$(LIBFT_DIR) -I$(MINILIB_DIR) -c $< -o $@

objs_bonus/%.o: srcs_bonus/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_BONUS) -I$(LIBFT_DIR) -I$(MINILIB_DIR) -c $< -o $@


$(MINILIB):
	@$(MAKE) -C $(MINILIB_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

bonus: $(NAME_BONUS)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MINILIB_DIR)

fclean: clean
	rm -rf $(MINILIB)
	rm -rf $(LIBFT)
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean $(NAME)

re-bonus: fclean $(NAME_BONUS)

norm:
	norminette ./srcs ./includes | grep Error || echo "OK"

norm_bonus:
	norminette ./srcs_bonus ./includes_bonus | grep Error || echo "OK"

.PHONY: all fclean clean re bonus norm
