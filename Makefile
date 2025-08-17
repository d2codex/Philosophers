# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:33:55 by diade-so          #+#    #+#              #
#    Updated: 2025/08/15 16:39:38 by diade-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = philo
LIB = libphilo.a

CC = cc
FLAGS = -Wall -Werror -Wextra -g3 -lpthread
INCLUDES = -I./includes

SRC_DIR = src
OBJ_DIR = obj
BONUS_DIR = bonus

# Source files
SRC_FILES = src/main.c \
	    src/parse.c \
	    src/errors.c \
	    src/init.c \
	    src/num_utils.c \
	    src/char_utils.c \
	    src/time.c\
	    print.c \
	    routine.c \
	    monitor.c 

SHARED = src/parse.c \
	 src/errors.c

BONUS_FILES = #add bonus src files here e.g. bonus/bonus1.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

SHARED_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SHARED:.c=.o)))

BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_FILES:.c=.o)))

ALL_BONUS_OBJ = $(BONUS_OBJ) $(SHARED_OBJ)

# **************************************************************************** #
#                                   Rules                                      #
# **************************************************************************** #

all: $(NAME) $(LIB)

# Build executable from objects
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

# Build static lib without main.o so tests can provide main()
$(LIB): $(filter-out $(OBJ_DIR)/main.o, $(OBJ))
	ar rcs $(LIB) $^

# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/philo.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c includes/philo.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

bonus: $(ALL_BONUS_OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $(ALL_BiONUS_OBJ) -o philo_bonus

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(LIB) philo_bonus

re: fclean all

.PHONY: all clean fclean re bonus
