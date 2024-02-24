CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

NAME = philo_bonus
CFILES = philo_bonus.c philo_tools_1_bonus.c philo_init_bonus.c philo_parsing_bonus.c philo_routine_bonus.c
OFILES = $(CFILES:.c=.o)
INCLUDES = philo_bonus.h

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