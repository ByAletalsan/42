# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 09:07:26 by atalaver          #+#    #+#              #
#    Updated: 2022/11/02 10:21:52 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/11/01 20:39:44 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = ft_utils.c push_swap.c ft_movements.c
OBJECTS = $(SOURCES:.c=.o)

LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: push_swap

bonus: push_swap

push_swap: push_swap.o libft
	$(CC) -o $@ $< $(LIBFT)

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean
	
fclean: clean
	rm -f push_swap libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re