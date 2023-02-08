# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 09:14:31 by atalaver          #+#    #+#              #
#    Updated: 2023/02/08 16:37:25 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=so_long
LIBFT = libft/libft.a
SRC:=src/so_long.c\
	 src/ft_check_map.c\
	 src/ft_read_map.c\
	 src/ft_move_player.c\
	 src/ft_utils.c\
	 src/ft_render_map.c\
	 src/ft_free.c\
	 src/ft_check_ruta.c
OBJ=$(SRC:.c=.o)
SRC_BONUS:=src_bonus/so_long_bonus.c\
	 src_bonus/ft_check_map_bonus.c\
	 src_bonus/ft_read_map_bonus.c\
	 src_bonus/ft_move_player_bonus.c\
	 src_bonus/ft_utils_bonus.c\
	 src_bonus/ft_render_map_bonus.c\
	 src_bonus/ft_free_bonus.c\
	 src_bonus/ft_check_ruta_bonus.c
OBJ_BONUS=$(SRC_BONUS:.c=.o)
NEXTLINE:=get_next_line/get_next_line_bonus.c \
		  get_next_line/get_next_line_utils_bonus.c
OBJNEXTLINE=$(NEXTLINE:.c=.o)
CC:=gcc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(OBJNEXTLINE) ml
	$(CC) $(OBJ) $(OBJNEXTLINE) -g -framework OpenGL -framework AppKit -o $(NAME) mlx/libmlx.a libft/libft.a

bonus: $(LIBFT) $(OBJ_BONUS) $(OBJNEXTLINE) ml
	$(CC) $(OBJ_BONUS) $(OBJNEXTLINE) -g -framework OpenGL -framework AppKit -o $(NAME) mlx/libmlx.a libft/libft.a

ml:
	make -C mlx

$(LIBFT):
	$(MAKE) bonus -C ./libft

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_BONUS)
	rm -rf $(OBJNEXTLINE)
	$(MAKE) clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C ./libft