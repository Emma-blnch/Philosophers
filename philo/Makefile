NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c srcs/data_init.c srcs/free_resources.c srcs/parsing.c \
srcs/safe_handle.c srcs/utils.c srcs/dinner.c srcs/get_and_set.c

OBJS = $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re