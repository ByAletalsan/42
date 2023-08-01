# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 12:23:02 by atalaver          #+#    #+#              #
#    Updated: 2023/07/27 18:28:48 by dvasco-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=gcc
CFLAGS=-Wall -Wextra -Werror
LIBFT=libft/libft.a
READLINE=-lreadline
SRC=bonus_wildcard.c clean_cmd_utils.c clean_cmd.c ejecutor.c enviro.c\
fd_gestion.c find_operator_utils.c find_operator.c ft_cd.c io_gestion.c\
main.c miniutils1.c procreacion.c procreacion2.c some_builtins.c\
some_builtins2.c some_builtins3.c tree_main.c utils_ejecutor.c utils_generic.c
OBJ=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(READLINE)

bonus: all

$(LIBFT):
	$(MAKE) bonus -C ./libft

clean:
	rm -rf $(OBJ)
	$(MAKE) clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: clean fclean re all bonus
