# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 09:14:31 by atalaver          #+#    #+#              #
#    Updated: 2022/12/20 21:26:34 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=so_long
LIBFT = libft/libft.a
SRC:=so_long.c\
	 src/ft_check_map.c\
	 src/ft_read_map.c\
	 src/ft_move_player.c\
	 src/ft_utils.c\
	 src/ft_render_map.c\
	 src/ft_free.c
OBJ=$(SRC:.c=.o)
NEXTLINE:=get_next_line/get_next_line_bonus.c \
		  get_next_line/get_next_line_utils_bonus.c
OBJNEXTLINE=$(NEXTLINE:.c=.o)
CC:=gcc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I./libft/include -I./include -Imlx_linux -c $< -o $@

$(NAME): $(LIBFT) $(OBJ) $(OBJNEXTLINE) ml
	$(CC) $(OBJ) $(OBJNEXTLINE) -framework OpenGL -framework AppKit -o $(NAME) mlx/libmlx.a libft/libft.a

linux: $(LIBFT) $(OBJ) $(OBJNEXTLINE)
	$(CC) $(CFLAGS) -L./libft -lft $(OBJ) $(OBJNEXTLINE) -Lmlx_linux mlx_linux/libmlx.a libft/libft.a -lft -L./libft -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

ml_linux:
	make -C mlx_linux

ml:
	make -C mlx

$(LIBFT):
	$(MAKE) bonus -C ./libft