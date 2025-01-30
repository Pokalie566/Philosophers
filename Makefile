# Makefile pour le projet Philosopher

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC_DIR = src
INCLUDE_DIR = includes
OBJ_DIR = obj

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/philosopher.c $(SRC_DIR)/utils.c $(SRC_DIR)/monitor.c
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: $(NAME)

# Create the executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

# Compile .c files to .o files in the obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/philo.h
	@mkdir -p $(OBJ_DIR) # Ensure the obj directory exists
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJ)

# Remove object files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all
