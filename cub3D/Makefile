# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 12:44:21 by atalaver          #+#    #+#              #
#    Updated: 2023/10/06 14:37:20 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft/libft.a
MLX42 = MLX42/libmlx42.a
SRC = main.c src/load_data_1.c src/load_data_2.c src/load_data_3.c src/load_data_4.c\
	src/raycast.c src/raycast_2.c src/minimap.c src/print_textures.c\
	src/print_textures_2.c src/tx/tx_no.c src/tx/tx_so.c src/tx/tx_we.c\
	src/tx/tx_ea.c src/tx/tx_door_v.c src/tx/tx_door_h.c src/hooks/hook.c\
	src/hooks/hooks_wasd.c src/load_mlx.c
OBJ = $(SRC:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
FLAGS_MLX_LINUX = -Iinclude -ldl -lglfw -pthread -lm

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJ)
	$(CC) $(OBJ) $(FLAGS_MLX) -o $(NAME) libft/libft.a MLX42/libmlx42.a

linux: $(LIBFT)
	$(CC) $(SRC) -o cub3D libft/libft.a MLX42_Linux/build/libmlx42.a $(FLAGS_MLX_LINUX)

$(LIBFT):
	$(MAKE) bonus -C ./libft

$(MLX42):
	$(MAKE) -C ./MLX42

clean:
	rm -rf $(OBJ)
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./MLX42

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./MLX42

re: fclean all

.PHONY: all clean fclean re