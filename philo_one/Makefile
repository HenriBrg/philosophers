NAME = philo_one

FLAGS = -Wall -Wextra -Werror

SRCS = main.c utils.c init.c actions.c

OBJS = ${SRCS:.c=.o}

DEBUG = -g -fsanitize=address

# ifndef VERBOSE
# .SILENT:
# endif

all: $(NAME)

.c.o:
	gcc $(FLAGS) -c $< -o $@ -lpthread

$(NAME): $(OBJS)
	gcc $(FLAGS) $(SRCS) -o $(NAME) -lpthread

run1: $(NAME)
	./philo_one 4 410 200 200

run2: $(NAME)
	./philo_one 4 310 200 100

run3: $(NAME)
	./philo_one 4 410 200 200 2

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
