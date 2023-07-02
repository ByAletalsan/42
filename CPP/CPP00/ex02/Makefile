# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 10:50:29 by atalaver          #+#    #+#              #
#    Updated: 2023/07/02 11:14:52 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=tests
SRC=tests.cpp Account.cpp
OBJ=$(SRC:.cpp=.o)
CC=c++
#FLAGS=-Wall -Werror -Wextra
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