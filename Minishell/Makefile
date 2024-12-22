NAME = minishell

FLAGS = -Wall -Werror -Wextra -L./libft -lft -lreadline

BUILT_IN = ./built_in/cd.c ./built_in/export.c ./built_in/pwd.c ./built_in/echo.c \
		./built_in/env.c ./built_in/unset.c ./built_in/exit.c ./built_in/export_utils.c

HANDLE_SIGNAL = ./srcs/handle_signal/handle_signal.c

LEXER = ./srcs/lexer/tokenizer.c ./srcs/lexer/token_creation.c ./srcs/lexer/token_utils.c \
		./srcs/lexer/fd_handling.c

CHECK_TOKENS = ./srcs/check_tokens/utils.c ./srcs/check_tokens/analyze_tokens.c

EXPANDER = ./srcs/expander/expander.c ./srcs/expander/expand_helpers.c ./srcs/expander/expander_utils.c \
				./srcs/expander/expand_token_utils.c ./srcs/expander/expand_token.c \
				./srcs/expander/process_word.c 

HANDLE_HEREDOC = ./srcs/handler_heredoc/heredoc.c ./srcs/handler_heredoc/heredoc_utils_1.c ./srcs/handler_heredoc/heredoc_utils.c

HANDLE_INPUT = ./srcs/handle_input/process_line_utils.c ./srcs/handle_input/process_input.c

INIT = ./srcs/init/init_data.c

PARSER = ./srcs/parser/free_ast.c ./srcs/parser/init_utils.c ./srcs/parser/parse_utils.c ./srcs/parser/parse.c \
			./srcs/parser/redirection_utils.c

UTILS = ./srcs/utils/mns_utils.c ./srcs/utils/env_utils.c

EXEC = ./srcs/exec/exec.c ./srcs/exec/exec_redir.c ./srcs/exec/exec_utils.c ./srcs/exec/exec_utils1.c

SRCS =  ${LEXER} ${CHECK_TOKENS} ${EXPANDER} ${PARSER} ${UTILS} ${BUILT_IN}  ${EXEC}\
		${HANDLE_INPUT} ${INIT}  ${HANDLE_HEREDOC} ${HANDLE_SIGNAL} ./srcs/main.c

OBJS = ${SRCS:.c=.o}


# Couleurs
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

all : ${NAME}

.c.o :
	@echo "${YELLOW}Compiling $<...${RESET}"
	@cc -c -Wall -Werror -Wextra  $< -o ${<:.c=.o}

${NAME} : ${OBJS}
	@make --no-print-directory bonus -C ./libft
	@cc -o ${NAME} ${OBJS} ${FLAGS}
	@echo "${CYAN}${NAME} has been successfully built!${RESET}"

clean :
	@echo "${RED}Cleaning object files...${RESET}"
	@make --no-print-directory clean -C ./libft
	@rm -rf ${OBJS}

fclean : clean
	@echo "${RED}Performing full clean...${RESET}"
	@make --no-print-directory fclean -C ./libft
	@rm -rf .history_file
	@rm -rf ${NAME}

re: fclean all

.PHONY: re fclean clean all
