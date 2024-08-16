CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
LIBFTDIR = 42_libft
LIBFT = $(LIBFTDIR)/libft.a
PARS = parsing/parsing.c parsing/dollar_sign.c parsing/prompt.c parsing/redirection_token.c parsing/signals.c parsing/utils.c parsing/free.c parsing/token.c
EXEC = main.c multidimensional.c multidimensional_utils.c env.c builtins.c command.c 
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
