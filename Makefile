NAME	= philo
BONUS_NAME = philo_bonus
CFLAGS	= -Wextra -Wall -Werror -pthread

SRC			= src/philo.c src/philosophy.c src/helper.c src/philo_food.c
# BONUS_SRC 	= 

SRC_DIR		= src
OBJ_DIR		= obj
# BONUS...

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# bonus..

all: $(NAME)
# bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
# $(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c | $(BONUS_OBJ_DIR)
# @$(CC) $(CFLAGS) -o $@ -c $< 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
# $(BONUS_OBJ_DIR):
# mkdir -p $(BONUS_OBJ_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)

# $(BONUS_NAME): $(BONUS_OBJ)
# @$(CC) $(BONUS_OBJ) $(LIBS) $(HEADERS) -o $(BONUS_NAME) 

clean:
	rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re