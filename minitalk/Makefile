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

SOURCES = ft_server.c ft_client.c
OBJECTS = $(SOURCES:.c=.o)

LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

bonus: server client

server: ft_server.o libft
	$(CC) -o $@ $< $(LIBFT)

client: ft_client.o libft
	$(CC) -o $@ $< $(LIBFT)

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean
	
fclean: clean
	rm -f server client libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re