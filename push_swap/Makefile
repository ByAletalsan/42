# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/11/08 15:16:23 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = ft_utils.c push_swap.c ft_movements.c ft_logic.c ft_order_to_five.c\
ft_check_arg.c ft_utils_two.c ft_order.c

LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: push_swap

bonus: push_swap

push_swap: runlibft
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LIBFT)

runlibft:
	make -C libft bonus

clean:
	$(MAKE) -C libft clean
	
fclean: clean
	rm -f push_swap
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re