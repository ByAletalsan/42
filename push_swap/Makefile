# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/11/13 12:38:52 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=push_swap
LIBFT = libft/libft.a
MAIN:=src/push_swap.c
SRC:=src/ft_utils.c \
	 src/ft_utils_two.c \
	 src/ft_order.c \
	 src/ft_order_to_five.c \
	 src/ft_movements.c \
	 src/ft_logic.c \
	 src/ft_check_arg.c \
	 src/ft_push_start.c

BONUS:=bonus/checker_bonus.c \
	   bonus/ft_logic_bonus.c \
	   bonus/ft_movements_bonus.c \
	   bonus/ft_utils_bonus.c

NEXTLINE:=get_next_line/get_next_line_bonus.c \
		  get_next_line/get_next_line_utils_bonus.c

COMPILED_OBJS=$(shell find . -name '*.o')
OBJMAIN=$(MAIN:.c=.o)
OBJ=$(SRC:.c=.o)
OBJBONUS=$(BONUS:.c=.o)
OBJNEXTLINE=$(NEXTLINE:.c=.o)
IFLAGS=-I./libft/include -I./include
LFLAGS=-L./libft
LIBS=-lft
CFLAGS=-Wall -Wextra -Werror
CC=gcc

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MAIN)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(MAIN) -o $(NAME) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

bonus: $(NAME) $(OBJBONUS) $(OBJNEXTLINE)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(OBJBONUS) $(OBJNEXTLINE) -o checker $(LIBS)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(MAKE) clean -C ./libft
	rm -rf $(COMPILED_OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)
	rm -rf checker

re: fclean all

.PHONY: all clean fclean re