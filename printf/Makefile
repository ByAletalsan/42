# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 20:35:21 by atalaver          #+#    #+#              #
#    Updated: 2022/10/16 22:54:30 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_print_bonus.c ft_print_char.c ft_print_hex.c ft_print_int.c\
ft_print_memory.c ft_print_string.c ft_print_uint.c ft_printf.c\
ft_struct_bonus.c
OBJS	= ${SRCS:.c=.o}
LIBFT	= libft/ft_memset.c libft/ft_bzero.c libft/ft_strlen.c libft/ft_atoi.c\
libft/ft_isdigit.c libft/ft_isalpha.c libft/ft_isprint.c libft/ft_isascii.c\
libft/ft_isalnum.c libft/ft_memchr.c libft/ft_memcpy.c libft/ft_striteri.c\
libft/ft_memcmp.c libft/ft_memmove.c libft/ft_strchr.c libft/ft_strdup.c\
libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strncmp.c libft/ft_toupper.c\
libft/ft_tolower.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_calloc.c\
libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putnbr_fd.c\
libft/ft_putendl_fd.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c\
libft/ft_strmapi.c libft/ft_itoa.c libft/ft_split.c libft/ft_lstnew_bonus.c\
libft/ft_lstadd_front_bonus.c libft/ft_lstsize_bonus.c libft/ft_lstlast_bonus.c\
libft/ft_lstadd_back_bonus.c libft/ft_lstdelone_bonus.c\
libft/ft_lstclear_bonus.c libft/ft_lstiter_bonus.c libft/ft_lstmap_bonus.c
LOBJS	= ${LIBFT:.c=.o}
INCS	= ft_printf.h
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
	${MAKE} -C libft fclean

re: fclean all

bonus: re
	${LIB} ${NAME} ${OBJS} ${LOBJS}
	${RL} ${NAME}

.PHONY: all re clean fclean bonus