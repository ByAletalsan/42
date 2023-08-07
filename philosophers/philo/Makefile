# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 15:04:53 by atalaver          #+#    #+#              #
#    Updated: 2023/08/07 11:27:28 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

RS = main.c\
	 ft_libft.c\
	 ft_utils.c\
	 ft_utils2.c\
	 ft_pthread.c
OBJ = $(RS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Werror -Wextra $(OBJ) -o $(NAME) -pthread

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re