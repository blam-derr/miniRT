NAME = miniRT

CC = cc

CFLAGS = -Wextra -Wall -Werror -O3 -march=native

MINILIB = ./libs/minilibx/libmlx_Linux.a

MINILIB_DIR = ./libs/minilibx

MINILIB_HDR = ./libs/minilibx/mlx.h

LIBFT = ./libs/libft/libft.a

LIBFT_DIR = ./libs/libft

LIBFT_HDR = ./libs/libft/libft.h

INC = ./includes

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

OBJS = $(patsubst ./srcs/%.c,./objs/%.o,$(SRCS))

$(NAME): $(OBJS) $(MINILIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MINILIB_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lXext -lX11 -lm -lz -lft

objs/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -I$(LIBFT_DIR) -I$(MINILIB_DIR) -c $< -o $@

$(MINILIB):
	@$(MAKE) -C $(MINILIB_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

bonus: $(NAME)

clean:
	rm -rf $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MINILIB_DIR)

fclean: clean
	rm -rf $(MINILIB)
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re: fclean $(NAME)

re-bonus: fclean bonus

norm:
	norminette ./srcs ./includes | grep Error || echo "OK"

.PHONY: all fclean clean re bonus norm
