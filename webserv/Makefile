# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:25:39 by atalaver          #+#    #+#              #
#    Updated: 2023/11/29 18:57:20 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= c++
NAME= webserv
CFLAGS= -Wall -Wextra -Werror -std=c++98
SRC=  srcs/Parse.cpp srcs/Server.cpp srcs/Location.cpp srcs/Cgi.cpp srcs/Request.cpp srcs/Response.cpp srcs/webserv.cpp srcs/utils.cpp srcs/Client.cpp srcs/manage_client.cpp
OBJ= $(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
