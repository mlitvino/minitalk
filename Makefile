# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 17:29:24 by mlitvino          #+#    #+#              #
#    Updated: 2024/12/27 18:53:37 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

CL_NAME = client
SV_NAME = server
LIBFT = libft.a

CL_SRC = client.c
SV_SRC = server.c

CL_OBJ = $(CL_SRC:.c=.o)
SV_OBJ = $(SV_SRC:.c=.o)

.SECONDARY: $(CL_OBJ) $(SV_OBJ)

all: $(CL_NAME) $(SV_NAME)

$(CL_NAME): $(CL_OBJ)
	$(CC) $(CL_OBJ) $(LIBFT) -o $@

$(CL_OBJ): $(CL_SRC)
	$(CC) -c $(CFLAGS) $?

$(SV_NAME): $(SV_OBJ)
	$(CC) $(SV_OBJ) $(LIBFT) -o $@

$(SV_OBJ): $(SV_SRC)
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(CL_OBJ) $(CV_OBJ)

fclean: clean
	rm -f $(CL_NAME) $(SV_NAME)

re: fclean all

.PHONY: all clean fclean re
