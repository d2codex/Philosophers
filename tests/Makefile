# Test Makefile
#
# Builds and links test executable against the philo static library.
# - Compiles test sources into obj/ within the test directory.
# - Calls the philo Makefile in parent directory to build libphilo.a if needed.
# - Cleans test objects and executables in test directory.
# - Also calls philo Makefile clean and fclean targets to clean philo objects 
#   and libphilo.a.
#
# Usage:
#   make        # Build tests and library if needed
#   make clean  # Remove test objects and call philo clean
#   make fclean # Remove test objects, executables, and call philo fclean to
#		  remove library

NAME = test
CC = cc
FLAGS = -Wall -Werror -Wextra -I../includes -g3
OBJ_DIR = obj

TEST_SRC = test.c
TEST_OBJ = $(OBJ_DIR)/test.o
LIB = ../libphilo.a
 
all: $(NAME)

$(NAME): $(LIB) $(TEST_OBJ)
	$(CC) $(FLAGS) $(TEST_OBJ) $(LIB) -o $@

$(LIB):
	@$(MAKE) -C .. libphilo.a

$(OBJ_DIR)/%.o: %.c ../includes/philo.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(MAKE) -C .. clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C .. fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
