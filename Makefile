NAME 		= cub3d

CC 			= cc
RM			= rm -f

CFLAGS 		+= -Wall -Wextra -Werror -Iinclude -g
CLINKS		= -ldl -lglfw -pthread -lm

MLX			= minilibx
LIBMLX 		= $(MLX)/libmlx42.a

FT			= libft
LIBFT		= $(FT)/libft.a

SRC 		= src/main.c \
				src/parsing/error.c \
				src/parsing/parsing_data.c \
				src/parsing/parsing_map.c \
				src/parsing/init.c \
				src/parsing/init_texture.c \
				src/utils/ft_puterror.c \
				src/utils/ft_pixel.c \
				src/utils/mlx_fill_image.c \
				src/utils/ft_len_tab.c \
				src/game/start.c \
				src/game/minmap_manager.c \
				src/game/move.c \
				src/game/raycasting.c \
				src/utils/is_wall.c
OBJ 		= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT) $(LIBMLX) $(CLINKS)

$(LIBMLX): $(MLX)
	cmake $(MLX) -B $(MLX)	
	$(MAKE) -C $(MLX)

$(LIBFT): $(FT)
	$(MAKE) -C $(FT)

$(MLX):
	git clone https://github.com/kodokaii/MLX42.git $(MLX)

$(FT):
	git clone https://github.com/Ratsock6/libft.git $(FT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if [ -d "$(MLX)" ]; then $(MAKE) clean -C $(MLX); fi
	if [ -d "$(FT)" ]; then $(MAKE) clean -C $(FT); fi
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBMLX)
	$(RM) $(LIBFT)
	$(RM) $(NAME)

clear: fclean
	$(RM) -r $(FT)
	$(RM) -r $(MLX) 

re: fclean
	$(MAKE) -j$(nproc)

.PHONY:		all bonus clear clean fclean re
