# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 16:04:33 by atamas            #+#    #+#              #
#    Updated: 2024/08/19 16:04:33 by atamas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
LIBFTDIR = 42_libft
LIBFT = $(LIBFTDIR)/libft.a
PARS = parsing/parsing.c parsing/dollar_sign.c parsing/prompt.c \
parsing/redirection_token.c parsing/signals.c parsing/utils.c \
parsing/print_test.c parsing/free.c parsing/token.c parsing/dollar_sign2.c \
parsing/loop.c parsing/redirection_no_spaces.c parsing/utils2.c
EXEC = main.c multidimensional.c multidimensional_utils.c env.c \
	builtins_first.c builtins_sec.c command.c command_utils.c error.c \
	command_utils2.c
SRC = $(PARS) $(EXEC)
OBJS = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all fclean clean re
