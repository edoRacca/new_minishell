CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Wpedantic
NAME = minishell

SRCS =  main.c \
		env_functions.c path_functions.c signals.c utils.c \
		history.c parsing.c token_functions.c token_functions_2.c

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
