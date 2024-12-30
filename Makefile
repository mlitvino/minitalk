# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 17:29:24 by mlitvino          #+#    #+#              #
#    Updated: 2024/12/30 12:12:40 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLD_DIR) -I$(LIBFT_DIR)/$(INCLD_DIR)

CL_NAME = client
SV_NAME = server
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = ./sources
OBJ_DIR = ./objects
LIBFT_DIR = ./libft
INCLD_DIR = ./includes

CL_SRC = $(SRC_DIR)/client.c
SV_SRC = $(SRC_DIR)/server.c
INCLD = $(INCLD_DIR)/minitalk.h

CL_OBJ = $(OBJ_DIR)/client.o
SV_OBJ = $(OBJ_DIR)/server.o

.SECONDARY: $(CL_OBJ) $(SV_OBJ)

all: $(LIBFT) $(SV_NAME) $(CL_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(SV_OBJ): $(SV_SRC) $(INCLD) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CL_OBJ): $(CL_SRC) $(INCLD) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) all
	make -C $(LIBFT_DIR) bonus

$(SV_NAME): $(SV_OBJ) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(SV_OBJ) $(LIBFT) -o $@

$(CL_NAME): $(CL_OBJ) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(CL_OBJ) $(LIBFT) -o $@

clean:
	rm -f $(CL_OBJ) $(SV_OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(CL_NAME) $(SV_NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
