## arguments

NAME 	= libft.a
CFLAGS 	= -Wall -Wextra -Werror
CC 		= cc

SRC_FILES = ft_bzero.c ft_isdigit.c ft_memcpy.c ft_strnstr.c \
			ft_isalnum.c ft_isprint.c ft_memmove.c ft_strrchr.c \
			ft_isalpha.c ft_memchr.c ft_memset.c ft_strlen.c ft_tolower.c \
			ft_isascii.c ft_memcmp.c ft_strchr.c ft_strncmp.c ft_toupper.c \
			ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
			ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c  ft_strlcpy.c ft_strlcat.c \
			ft_atoi.c get_next_line.c get_next_line_utils.c ft_printf.c ft_printf_utils.c \
			ft_printf_utils2.c

BONUS_FILES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			  ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
			  ft_lstmap_bonus.c

ALL_FILES = $(SRC_FILES) $(BONUS_FILES)

OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ_ALL = $(ALL_FILES:.c=.o)

### rules 

all: $(NAME)  

$(NAME): $(OBJ_FILES)
	ar -rcs $(NAME) $(OBJ_FILES)	

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ_ALL)
	ar -rcs $(NAME) $(OBJ_ALL)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
