# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/11/08 09:57:21 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

bonus: server client

server: $(LIBFT)
	$(CC) $(CFLAGS) -o server ft_server.c $(LIBFT)

client: $(LIBFT)
	$(CC) $(CFLAGS) -o client ft_client.c $(LIBFT)

$(LIBFT):
	make -C libft bonus

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C libft clean
	
fclean: clean
	rm -f server client
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re