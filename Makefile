CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -lreadline -Wpedantic
NAME = minishell

SRC = main.c env_functions.c

OBJ = $(SRC:.c=.o)

LIBFT_SRC = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c \
       libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c \
       libft/ft_itoa.c libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstclear.c \
       libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c \
       libft/ft_lstnew.c libft/ft_lstsize.c libft/ft_putchar_fd.c \
       libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c \
       libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c \
       libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c \
       libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c \
       libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c

LIBFT = $(LIBFT_SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo Linking... {$(NAME)}...
	$(CC) $(OBJ) -I libft.h -o $(NAME) $(CFLAGS) 

clean:
	@echo Cleaning...
	@rm -f $(OBJ)

fclean: clean
	@echo Cleaning...
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
