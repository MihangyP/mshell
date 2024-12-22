NAME = libft.a

srcs = ft_strlen.c \
		ft_bzero.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_isalnum.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		split_mns.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

srcs_bonus = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 

OBJS = ${srcs:.c=.o}

OBJS_BONUS = ${srcs_bonus:.c=.o}

INCLUDE = ./libft.h

CC = cc

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

.c.o:
	@${CC} ${FLAGS} -I. -c $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${INCLUDE}
	@ar rc ${NAME} ${OBJS}

bonus: ${OBJS} ${OBJS_BONUS}
	@ar rc ${NAME} ${OBJS} ${OBJS_BONUS}

clean:
	@rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: re clean fclean all bonus
