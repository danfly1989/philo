NAME = philo
CC = cc
CFLAGS = -g -O0 -Wall -Wextra -Werror -pthread -I./include
SRC = src/philo.c src/utils.c src/sleep.c src/philo_routine.c src/monitor_routine.c src/ft_print.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
