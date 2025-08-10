# @file       Makefile
# @brief      Makefile to build the test executable by linking test code with
#             the philo static library (libphilo.a) built from the main project.
#
# @details
# This Makefile:
# - Ensures the philo static library (libphilo.a) is built by invoking the main
#   Makefile in the parent directory.
# - Compiles the test source file (test.c) into an object file.
# - Links the test object file with the philo static library to produce the
#   final test executable.
#
# Targets:
# - all: Builds the test executable.
# - clean: Removes test object files.
# - fclean: Removes test object files and the test executable.
# - re: Rebuilds everything from scratch.
#
# Variables:
# - NAME: Name of the test executable.
# - CC: Compiler to use.
# - CFLAGS: Compiler flags including warnings and includes.
# - OBJ_DIR: Directory to store object files.
# - TEST_SRC: The test source file.
# - TEST_OBJ: The object file for the test source.
# - LIB: Path to the philo static library.
 
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
