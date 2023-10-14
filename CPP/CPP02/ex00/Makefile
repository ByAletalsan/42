# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 09:10:46 by atalaver          #+#    #+#              #
#    Updated: 2023/10/14 15:11:23 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=main
SRC=main.cpp Fixed.cpp
OBJ=$(SRC:.cpp=.o)
CC=c++
FLAGS=-Wall -Werror -Wextra
VERSION=-std=c++98

%.o: %.cpp
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
