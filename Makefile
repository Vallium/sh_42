# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by aalliot           #+#    #+#              #
#    Updated: 2015/02/22 00:29:54 by aalliot         ###   ########.fr         #
#                                                                              #
# **************************************************************************** #

STATIC_EXE	= ft_minishell2
DEBUG_EXE	= ft_minishell2_debug

SRC		=	main.c		\
			env.c		\
			command.c	\
			built_in.c	\
			unsetenv.c	\
			free.c		\
			parse.c

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
FLAGS		= -Wall -Wextra
SRC	+=

endif
ifeq ($(UNAME_S),Darwin)
FLAGS		= -Wall -Wextra -Werror
SRC	+=

endif

STATIC_OBJ	= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
DEBUG_OBJ	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
LIBFT_STATIC= libft/libft.a
LIBFT_DEBUG	= libft/libft_debug.a
LIBFT_HEAD	= libft/includes/

CC			= gcc
NORMINETTE	= ~/project/colorminette/colorminette

$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR))

all: $(STATIC_EXE)

debug: $(DEBUG_EXE)

$(DEBUG_EXE): $(DEBUG_OBJ) $(LIBFT_DEBUG)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $(DEBUG_EXE) $(DEBUG_OBJ) $(LIBFT_DEBUG) $(FLAGS) -g
	@echo "\n\033[32mCompilation complete. (debug)\033[39m\n"

$(STATIC_EXE): $(STATIC_OBJ) $(LIBFT_STATIC)
	$(CC) -O3 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(STATIC_OBJ) $(LIBFT_STATIC) $(FLAGS)
	@echo "\n\033[32mCompilation complete. (realease)\n\033[39m"

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	$(CC) -O3 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(FLAGS)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(FLAGS) -g

$(LIBFT_STATIC):
	make -C libft/ libft.a

$(LIBFT_DEBUG):
	make -C libft/ libft_debug.a

.PHONY: clean fclean re debug norme

clean:
	@make -C libft clean
	@rm -f $(STATIC_OBJ) $(DEBUG_OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(STATIC_EXE) $(DEBUG_EXE)

norme:
	$(NORMINETTE) $(SRC_DIR)/ $(HEAD_DIR)/
	make -C libft norme

re: fclean
	make
