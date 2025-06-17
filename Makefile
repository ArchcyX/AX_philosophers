NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread
RM = rm -rf

SRC =	./src/error_exit.c		\
		./src/free_functions.c	\
		./src/philo.c			\
		./src/utils.c			\
		./src/init_thread.c		\
		./src/states.c			\
		./src/time_functions.c

OBJ_DIR = obj

OBJS = $(OBJ_DIR)/philo.o				\
       $(OBJ_DIR)/free_functions.o		\
       $(OBJ_DIR)/error_exit.o			\
       $(OBJ_DIR)/utils.o				\
       $(OBJ_DIR)/init_thread.o			\
       $(OBJ_DIR)/states.o				\
       $(OBJ_DIR)/time_functions.o

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\\U0001F4C1 \033[32m✓ build completed\033[0m"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "\033[1;33m✓ objects removed\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[31m✓ executable removed\033[0m --> $(NAME)"

re: fclean all

.PHONY: all clean fclean re