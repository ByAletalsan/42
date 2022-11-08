# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/11/08 19:31:00 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAIN = src/push_swap.c

SOURCES = src/ft_utils.c src/ft_movements.c src/ft_logic.c\
src/ft_order_to_five.c src/ft_check_arg.c src/ft_utils_two.c src/ft_order.c

SOURCESBONUS = bonus/checker_bonus.c bonus/ft_logic_bonus.c\
bonus/ft_movements_bonus.c bonus/ft_utils_bonus.c

NEXTLINE = get_next_line/get_next_line_bonus.c\
			get_next_line/get_next_line_utils_bonus.c\

LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: push_swap

bonus: checker

push_swap: runlibft
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LIBFT) $(MAIN)

checker: runlibft
	$(CC) $(CFLAGS) -o $@ $(SOURCESBONUS) $(LIBFT) $(SOURCES) $(NEXTLINE) -D BUFFER_SIZE

runlibft:
	make -C libft bonus

clean:
	$(MAKE) -C libft clean
	
fclean: clean
	rm -f push_swap
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re