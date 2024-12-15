# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 12:06:42 by pmihangy          #+#    #+#              #
#    Updated: 2024/12/09 16:23:38 by pmihangy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## GLOBAL VARIABLES
NAME = minishell
SRC = main.c 
UTILS_FILES = error.c free.c lst.c signals.c utils.c utils2.c
PARSER_FILES = parser.c tokenizer.c tokenizer_utils.c parsing_tokens.c  \
			   parsing_tokens_get_functions.c parsing_tokens_utils.c \
			   expander.c expander_utils.c cmd.c
EXEC_FILES = exec.c find_cmd.c builtins.c process.c wait.c
BUILTINS_FILES = cd.c pwd.c exit.c echo.c export.c export_utils.c unset.c env.c
SRC_FILES = $(addprefix src/, $(SRC))
SRC_FILES += $(addprefix src/utils/, $(UTILS_FILES))
SRC_FILES += $(addprefix src/parser/, $(PARSER_FILES))
SRC_FILES += $(addprefix src/exec/, $(EXEC_FILES))
SRC_FILES += $(addprefix src/builtins/, $(BUILTINS_FILES))
HEADER_FILE = ./include/minishell.h
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
INCLUDE = -I./include -I./libft
LIBFT = ./libft
LINKING = -L$(LIBFT) -lft -lreadline -lhistory

## RULES
all: $(NAME)

$(NAME): $(SRC_FILES) $(HEADER_FILE)
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
