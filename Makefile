NAME = codexion

CC = cc
FLAGS = -pthread -MMD -MP -g3 -I$(SRC)

# Folders
BUILD = build
SRC = coders

# Files
SRCS = \
	codexion.c \
	routine.c \
	routine_flow.c \
	routine_dongles.c \
	monitoring.c \
	error_handling/error_handling.c \
	parsing/initialization.c \
	parsing/verification.c \
	parsing/allocation.c \
	utils/action.c \
	utils/free.c \
	utils/time.c \
	utils/mutex.c

OBJS := $(SRCS:%.c=$(BUILD)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
