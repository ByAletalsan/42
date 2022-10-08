# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/09/26 10:59:43 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTS	= tests/main.c
TNAME	= test
TOBJS	= ${TESTS:.c=.o}
SRCS	= ${wildcard *.c}
OBJS	= ${SRCS:.c=.o}
LIBFT	= ${wildcard libft/*.c}
LOBJS	= ${LIBFT:.c=.o}
INCS	= ${wildcard *.h}
NAME	= libftprintf.a
CC	= gcc
FLAGS	= -Wall -Werror -Wextra
RM	= rm -f
LIB	= ar rc
RL	= ranlib

all: ${NAME}

.c.o:
	${CC} ${FLAGS} -c $< ${<:.c.o} -I.${INCS}

${NAME}: runlibft ${OBJS}
	${LIB} ${NAME} ${OBJS} ${LOBJS}
	${RL} ${NAME}

runlibft:
	make -C libft bonus

clean:
	${RM} ${OBJS}
	${MAKE} -C libft clean

fclean: clean
	${RM} ${NAME}
	${RM} ${TNAME}
	${MAKE} -C libft fclean

re: fclean all

test: re ${TOBJS}
	${CC} -g ${CFLAGS} ${TOBJS} -Llibft -lft -o ${TNAME}

bonus: re ${BOBJS}
	${LIB} ${NAME} ${OBJS} ${BOBJS}
	${RL} ${NAME}

norm :
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine *.h

.PHONY: all re clean fclean