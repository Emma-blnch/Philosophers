NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

MAKEFLAGS += --no-print-directory

SRCS = main.c init.c death.c forks.c threads.c utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re