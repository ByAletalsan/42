# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/09/24 21:23:25 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ar rcs
RM = rm -f

CC = gcc
CCFLAGS = -Wall -Wextra -Werror

NAME =  libftprintf.a

SOURCE = ft_printf.c

OBJ = $(SOURCE: .c=.o)

INCLUDE = libftprintf.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(LIB) $(NAME) $(OBJ)

makelibft:
	cd libft && make bonus

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re