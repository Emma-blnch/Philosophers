NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

MAKEFLAGS += --no-print-directory

SRCS = srcs/main.c srcs/data_init.c srcs/free_resources.c srcs/ft_atol.c srcs/utils.c \
srcs/dinner.c srcs/monitor.c srcs/safe_handle.c

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