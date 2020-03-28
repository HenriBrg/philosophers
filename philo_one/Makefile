NAME = philo_one

FLAGS = -Wall -Wextra -Werror

SRCS = main.c utils.c init.c actions.c

OBJS = ${SRCS:.c=.o}

# ifndef VERBOSE
# .SILENT:
# endif

all: $(NAME)

.c.o:
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(FLAGS) $(SRCS) -o $(NAME)

run: $(NAME)
	./philo_one 4 1000 1000 1000
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
