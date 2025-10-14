CFLAGS = -Wall -Wextra -Werror -I./include
SRC = src/philo.c src/utils.c src/sleep.c src/philo_routine.c src/monitor_routine.c src/ft_print.c
OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	 cc $(CFLAGS) $^ -o $@ -lpthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
