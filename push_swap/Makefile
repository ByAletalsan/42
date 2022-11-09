# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/11/09 12:48:36 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=push_swap
LIBFT = libft/libft.a
SRC:=src/push_swap.c \
	 src/ft_utils.c \
	 src/ft_utils_two.c \
	 src/ft_order.c \
	 src/ft_order_to_five.c \
	 src/ft_movements.c \
	 src/ft_logic.c \
	 src/ft_check_arg.c \
	 src/ft_push_start.c

COMPILED_OBJS=$(shell find . -name '*.o')
OBJ=$(SRC:.c=.o)
IFLAGS=-I./libft/include -I./include
LFLAGS=-L./libft
LIBS=-lft
CFLAGS=-Wall -Wextra -Werror
CC=gcc

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(MAKE) clean -C ./libft
	rm -rf $(COMPILED_OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re