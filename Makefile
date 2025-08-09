# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:33:55 by diade-so          #+#    #+#              #
#    Updated: 2025/08/09 20:25:38 by diade-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               Compiler & Flags                               #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Werror -Wextra -g3
INCLUDES = -I./includes

# **************************************************************************** #
#                                 Target Name                                  #
# **************************************************************************** #

NAME = philo

# **************************************************************************** #
#                                 Directories                                  #
# **************************************************************************** #

SRC_DIR = src
OBJ_DIR = obj
BONUS_DIR = bonus

# **************************************************************************** #
#                                Source Files                                  #
# **************************************************************************** #

SRC = $(addprefix $(SRC_DIR)/, main.c parse.c errors.c init.c num_utils.c \
	char_utils.c)

SHARED = parse.c errors.c

BONUS_SRC = $(addprefix $(BONUS_DIR)/, )

# **************************************************************************** #
#                                Object Files                                  #
# **************************************************************************** #

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

SHARED_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SHARED:.c=.o)))

BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_SRC:.c=.o)))

ALL_BONUS_OBJ = $(BONUS_OBJ) $(SHARED_OBJ)

# **************************************************************************** #
#                                   Rules                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

bonus: $(ALL_BONUS_OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $(ALL_BiONUS_OBJ) -o philo_bonus

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) philo_bonus

re: fclean all

.PHONY: all clean fclean re bonus
