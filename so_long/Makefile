# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 09:14:31 by atalaver          #+#    #+#              #
#    Updated: 2022/11/22 12:23:27 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=so_long
LIBFT = libft/libft.a
SRC:=so_long.c\
	 src/ft_check_map.c\
	 src/ft_check_map_two.c\
	 src/ft_read_map.c
OBJ=$(SRC:.c=.o)
NEXTLINE:=get_next_line/get_next_line_bonus.c \
		  get_next_line/get_next_line_utils_bonus.c
OBJNEXTLINE=$(NEXTLINE:.c=.o)
CC:=gcc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(LIBFT) $(OBJ) $(OBJNEXTLINE) ml
	$(CC) $(OBJ) $(OBJNEXTLINE) -framework OpenGL -framework AppKit -o $(NAME) mlx/libmlx.a libft/libft.a

ml:
	make -C mlx

$(LIBFT):
	$(MAKE) -C ./libft