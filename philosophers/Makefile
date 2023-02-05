# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 15:04:53 by atalaver          #+#    #+#              #
#    Updated: 2023/02/05 16:41:53 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

RS = main.c\
	 ft_libft.c\
	 ft_utils.c\
	 ft_pthread.c
OBJ = $(RS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Werror -Wextra $(OBJ) -o $(NAME) -pthread

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)