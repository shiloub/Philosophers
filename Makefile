NAME = philo
CC = gcc
CFLAGS = -pthread -Wall -Wextra -Werror
SRC = main.c \
		parse.c \
		ft_atoi.c \
		time.c \
		monitoring.c \
		take_forks.c \
		eat_n_sleep.c \
		routine.c \


OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) -o $@ -c $^ $(CFLAGS) 

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

