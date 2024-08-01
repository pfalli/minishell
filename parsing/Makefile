CC = gcc
CFLAGS = -Wall -Wextra -Werror

TARGET = minishell
SRC = main.c prompt.c lexing.c utils.c
OBJ = $(SRC:.c=.o)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
fclean:
	rm -f $(OBJ) $(TARGET)
.PHONY: all clean

valgrind --leak-check=full

valgrind --leak-check=full --show-leak-kinds=all

gcc -g -Wall -Wextra -Werror parsing.c prompt.c utils.c -lreadline