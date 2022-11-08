# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/11/08 18:53:57 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=paco
LIBFT = libft/libft.a
SRC:=ft_client.c \
	 ft_server.c

COMPILED_OBJS=$(shell find . -name '*.o')
OBJ=$(SRC:.c=.o)
IFLAGS=-I./libft/include -I./include
LFLAGS=-L./libft
LIBS=-lft
CFLAGS=-Wall -Wextra -Werror
CC=gcc

all: $(NAME)

$(NAME): server client

server: $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) ft_server.o -o server $(LIBS)

client: $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) ft_client.o -o client $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft

bonus: $(LIBFT) server client

clean:
	$(MAKE) clean -C ./libft
	rm -rf $(COMPILED_OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf client
	rm -rf server

re: fclean all

.PHONY: all bonus clean fclean re