# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 05:47:31 by atalaver          #+#    #+#              #
#    Updated: 2023/07/04 07:10:26 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=main
SRC=main.cpp Sed.cpp
OBJ=$(SRC:.cpp=.o)
CC=c++
FLAGS=-Wall -Werror -Wextra
VERSION=-std=c++98

%.o: %.c
	$(CC) $(FLAGS) $(VERSION) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(FLAGS) $(VERSION) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
