NAME = miniRT

CC = cc

CFLAGS = -Wextra -Wall -Werror -O3

MINILIB = ./libs/minilibx/libmlx_Linux.a

MINILIB_DIR = ./libs/minilibx

MINILIB_HDR = ./libs/minilibx/mlx.h

LIBFT = ./libs/libft/libft.a

LIBFT_DIR = ./libs/libft

LIBFT_HDR = ./libs/libft/libft.h

INC = ./includes

SRCS = ./srcs/main.c \
	   ./srcs/hooks.c \
	   ./srcs/utils/ft_atof.c \
	   ./srcs/utils/arrays/int_array_utils.c \
	   ./srcs/utils/arrays/string_array_utils.c \
	   ./srcs/utils/arrays/ft_split_charset.c \
	   ./srcs/utils/string/is_whitespace.c \
	   ./srcs/parser/parser.c \
	   ./srcs/parser/file_validation.c \
	   ./srcs/parser/dispatcher/dispatcher.c \
		 ./srcs/parser/dispatcher/parse_required.c \
		 ./srcs/parser/dispatcher/parse_objects.c

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
