# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eraccane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 11:59:39 by eraccane          #+#    #+#              #
#    Updated: 2023/11/21 20:06:09 by eraccane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
       ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
       ft_itoa.c  ft_memset.c ft_split.c ft_substr.c \
       ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
       ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
       ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
       ft_tolower.c ft_toupper.c 

NAME = libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Libft Done !"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

