CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

NAME = philo
CFILES = philo.c philo_tools_1.c philo_tools_2.c philo_init.c philo_parsing.c routine.c
OFILES = $(CFILES:.c=.o)
INCLUDES = philo.h

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Program Created"


$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OFILES)

fclean: clean
	@$(RM) $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Cleaning Done"

re: fclean all

.PHONY: all clean fclean re bonus