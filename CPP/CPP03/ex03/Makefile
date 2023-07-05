# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 05:43:09 by atalaver          #+#    #+#              #
#    Updated: 2023/07/05 08:10:04 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=main
SRC=main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp DiamondTrap.cpp
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
