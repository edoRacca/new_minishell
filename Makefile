CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Wpedantic
NAME = minishell

SRCS =  main.c \
		env_functions.c path_functions.c signals.c utils.c \
		history.c parsing.c token_functions.c token_functions_2.c \
		executing.c error_exit.c export.c error_exit_2.c \
		utils_2.c export_2.c unset.c echo.c utils_3.c \
		echo_2.c executing_2.c utils_4.c syntax.c pipe.c \
		redirections.c syntax_2.c redir_trunc.c utils_5.c \
		redir_input.c redir_hdoc.c utils_6.c pipe_2.c multiple_redirect.c \
		multiple_redirect_2.c utils_7.c multiple_redirect_3.c pipe_redir.c pipe_redir_2.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	@echo Compiling $<...
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@echo Linking... {$(NAME)}...
	@make -C libft/
	$(CC) $(CFLAGS) $(OBJ) -I include libft/libft.a -o $(NAME) -lreadline

clean:
	@echo Cleaning...
	@rm -f $(OBJ)
	@make clean -C libft/

fclean: clean
	@echo Cleaning...
	@rm -f $(NAME)
	@make fclean -C libft/

re: fclean all


.PHONY: clean fclean re all
