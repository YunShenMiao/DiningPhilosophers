NAME	= philo
CFLAGS	= -Wextra -Wall -Werror -pthread

SRC			= src/philo.c src/philosophy.c src/helper.c src/philo_food.c src/init.c src/monitor.c

SRC_DIR		= src
OBJ_DIR		= obj

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re