NAME = minishell
DIR_SRC = src/
LIBFT = libft/libft.a
CC = cc 
CFLAGS = -Wall -Wextra -Werror -ggdb 
LDFLAGS = -lreadline
RM = rm -f

SRCS =	$(wildcard $(DIR_SRC)*.c) \
		$(wildcard $(DIR_SRC)/parse/*.c) \

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

clean:
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all