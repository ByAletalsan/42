# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 15:04:53 by atalaver          #+#    #+#              #
#    Updated: 2023/08/09 17:24:12 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

RS = main.c\
	 ft_libft.c\
	 ft_utils.c\
	 ft_utils2.c\
	 ft_process.c
OBJ = $(RS:.c=.o)
CC=gcc
#DEBUG=-fsanitize=thread -g
FLAGS=-Wall -Werror -Wextra -pthread

.c.o:
	${CC} ${FLAGS} ${DEBUG} -c $< ${<:.c.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(DEBUG) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
