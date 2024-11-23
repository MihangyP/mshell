# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 12:06:42 by pmihangy          #+#    #+#              #
#    Updated: 2024/11/18 10:29:44 by irazafim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## ARGUMENTS
NAME = minishell
SRC = main.c 
SRC_FILES = $(addprefix src/, $(SRC))
UTILS_FILES = error.c
SRC_FILES += $(addprefix src/utils/, $(UTILS_FILES))
CC = cc -g
CFLAGS = -Wall -Wextra #-Werror
RM = rm -rf
INCLUDE = -I./include -I./libft
LIBFT = ./libft
LINKING = -L$(LIBFT) -lft -lreadline

## RULES
all: $(NAME)

$(NAME): $(SRC_FILES)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC_FILES) -o $(NAME) $(LINKING)

clean:
	make -C $(LIBFT) clean
	$(RM) *.o

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.donto ./$(NAME)

.PHONY: all clean fclean re
