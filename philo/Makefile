#-------------------------------------------------------CFLAGS---------------------------------------------------#
CFLAGS = -Wall -Wextra -Werror -pthread -g

#-------------------------------------------------------SRCS----------------------------------------------------#
SRC = \
	src/main.c \
	src/philosopher.c \
	src/utils.c \
	src/monitor.c

#-------------------------------------------------------OBJECTS--------------------------------------------------#
OBJ = $(SRC:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

#-------------------------------------------------------INCLUDES------------------------------------------------#
INC_DIR = includes
INCS = -I $(INC_DIR)

#-------------------------------------------------------NAME-----------------------------------------------------#
NAME = philo

#-------------------------------------------------------COLORS--------------------------------------------------#
BOLD = \033[1m
RESET = \033[0m
CYAN = \033[36m
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
DEFAULT = \033[39m

#-------------------------------------------------------RULES---------------------------------------------------#

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)>>> Philosopher is compiled ✅ <<<$(DEFAULT)"

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(dir $@)
	@$(eval CURR_OBJ=$(shell echo $$(($(CURR_OBJ) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURR_OBJ) * 100 / $(words $(SRC))))))
	@ \
	if [ $(PERCENT) -lt 25 ]; then \
		COLOR="$(RED)"; \
	elif [ $(PERCENT) -lt 50 ]; then \
		COLOR="$(YELLOW)"; \
	elif [ $(PERCENT) -lt 75 ]; then \
		COLOR="$(CYAN)"; \
	else \
		COLOR="$(GREEN)"; \
	fi; \
	printf "$${COLOR}($(BOLD)%3s%%$(RESET)$${COLOR})$(RESET) Compiling $(BOLD)$<$(RESET)\n" "$(PERCENT)"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(YELLOW)>>> Philosopher is cleaned 🧹 <<<$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)>>> Philosopher is fully cleaned 🧼 <<<$(DEFAULT)"

re: fclean all
