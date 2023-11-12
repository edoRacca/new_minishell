CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -lreadline -Wpedantic
NAME = minishell

SRC = 	main.c \
		type.c \
		ausiliary/helper.c \
		ausiliary/helper2.c \
		ausiliary/helper3.c \
		ausiliary/helper4.c \
		libft/ft_atoi.c \
		libft/ft_bzero.c \
		libft/ft_calloc.c \
		libft/ft_isalnum.c \
		libft/ft_isalpha.c \
		libft/ft_isascii.c \
		libft/ft_isdigit.c \
		libft/ft_isprint.c \
		libft/ft_memchr.c \
		libft/ft_memcmp.c \
		libft/ft_memcpy.c \
		libft/ft_memmove.c \
		libft/ft_memset.c \
		libft/ft_putnbr_fd.c \
		libft/ft_putchar_fd.c \
		libft/ft_putstr_fd.c \
		libft/ft_strchr.c \
		libft/ft_strrchr.c \
		libft/ft_strdup.c \
		libft/ft_strlcat.c \
		libft/ft_strlcpy.c \
		libft/ft_strlen.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \
		libft/ft_tolower.c \
		libft/ft_toupper.c \
		libft/ft_strjoin.c \
		libft/ft_itoa.c \
		libft/ft_striteri.c \
		libft/ft_strmapi.c \
		libft/ft_strtrim.c \
		libft/ft_split.c \
		libft/ft_putendl_fd.c \
		libft/ft_substr.c \
		libft/ft_strcpy.c \
		libft/ft_strcat.c \
		di_sistema/signal/signal.c \
		di_sistema/history/history.c \
		di_sistema/echo/echo.c \
		di_sistema/echo/echo2.c \
		di_sistema/execve/commands.c \
		di_sistema/export_unset_env/unset_env.c \
		di_sistema/export_unset_env/export.c \
		di_sistema/export_unset_env/export2.c \
		di_sistema/export_unset_env/export3.c \
		di_sistema/dir/directory.c \
		di_sistema/execve/flags.c \
		di_sistema/redirections/redirections.c \
		di_sistema/redirections/red_help.c \
		di_sistema/redirections/redirection_type.c \
		di_sistema/redirections/minor_redirection.c \
		split/split.c \
		split/split2.c \
		pipe/pipe.c \
		path/path.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	@echo Compiling $<...
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): libft $(OBJ)
	@echo Linking... {$(NAME)}...
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) 

clean:
	@echo Cleaning...
	@rm -f $(OBJ)

fclean: clean
	@echo Cleaning...
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
