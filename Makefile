# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 17:53:17 by fmontser          #+#    #+#              #
#    Updated: 2024/02/07 11:57:48 by fmontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 		+= --silent
MAKEFILE		:= Makefile

INC_DIR			:= include/
SRC_DIR			:= src/
OBJ_DIR			:= obj/
BIN_DIR			:= bin/
NAME			:= minishell
HDRS 			:= parser.h process.h prompt.h shell.h
SRCS 			:= main.c parser.c process.c prompt.c shell.c
OBJS			:= $(SRCS:.c=.o)

LIBFT_DIR		:= src/libft/
LIBFT_INC		:= src/libft/include
LIBFT			:= src/libft/lib/libft.a

CC				:= gcc
PERF_FLAGS		:= #-O3
CC_FLAGS		:= -Wall -Werror -Wextra -g -c $(PERF_FLAGS)
STD_LIBS		:= -lreadline
TEST_LEAKS		:= leaks -atExit --

# Builtins
ECHO			:= echo
ECHO_SRC_DIR	:= $(SRC_DIR)_echo/src/
ECHO_OBJ_DIR	:= $(SRC_DIR)_echo/obj/
ECHO_SRCS		:= echo.c
ECHO_OBJS		:= $(ECHO_SRCS:.c=.o)

CD				:= cd
CD_SRC_DIR		:= $(SRC_DIR)_cd/src/
CD_OBJ_DIR		:= $(SRC_DIR)_cd/obj/
CD_SRCS			:= cd.c
CD_OBJS			:= $(CD_SRCS:.c=.o)

CLEAN_TARGETS	=	$(wildcard $(addprefix $(OBJ_DIR), $(OBJS)))\
					$(wildcard $(addprefix $(ECHO_OBJ_DIR), $(ECHO_OBJS)))\
					$(wildcard $(addprefix $(CD_OBJ_DIR), $(CD_OBJS)))
FCLEAN_TARGETS	= $(wildcard $(addprefix $(BIN_DIR), $(NAME) $(ECHO) $(CD)))

COLOR_GREEN		:=\033[0;32m
COLOR_RED		:=\033[0;31m
COLOR_BLUE		:=\033[0;34m
COLOR_END		:=\033[0m

vpath %.h $(INC_DIR) $(LIBFT_INC)
vpath %.c $(SRC_DIR) $(ECHO_SRC_DIR) $(CD_SRC_DIR)
vpath %.o $(OBJ_DIR) $(ECHO_OBJ_DIR) $(CD_OBJ_DIR)
vpath % $(BIN_DIR)

all: $(NAME) $(LIBFT) $(ECHO) $(CD)

# Minishell compiler
$(NAME): $(OBJS) $(LIBFT)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(addprefix $(OBJ_DIR),$(OBJS)) $(LIBFT) -o $(BIN_DIR)$(NAME) $(STD_LIBS)
	@echo "$(COLOR_GREEN)write file: $(BIN_DIR)$@ $(COLOR_END)"

# Minishell linker
%.o : %.c $(HDRS) $(MAKEFILE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -I $(INC_DIR) -I $(LIBFT_INC) $(CC_FLAGS) $< -o $(OBJ_DIR)$@
	@echo "$(COLOR_GREEN)write file: $(OBJ_DIR)$@ $(COLOR_END)"

# Echo compiler
$(ECHO): $(ECHO_OBJS) $(LIBFT)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(addprefix $(ECHO_OBJ_DIR),$(ECHO_OBJS)) $(LIBFT) -o $(BIN_DIR)$(ECHO)
	@echo "$(COLOR_GREEN)write file: $(BIN_DIR)$@ $(COLOR_END)"

# Echo linker
$(ECHO_OBJS): $(ECHO_SRCS) $(MAKEFILE)
	@mkdir -p $(ECHO_OBJ_DIR)
	@$(CC) -I $(LIBFT_INC) $(CC_FLAGS) $< -o $(ECHO_OBJ_DIR)$@
	@echo "$(COLOR_GREEN)write file: $(ECHO_OBJ_DIR)$@ $(COLOR_END)"

# Cd compiler
$(CD): $(CD_OBJS) $(LIBFT)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(addprefix $(CD_OBJ_DIR),$(CD_OBJS)) $(LIBFT) -o $(BIN_DIR)$(CD)
	@echo "$(COLOR_GREEN)write file: $(BIN_DIR)$@ $(COLOR_END)"

# Cd linker
$(CD_OBJS): $(CD_SRCS) $(MAKEFILE)
	@mkdir -p $(CD_OBJ_DIR)
	@$(CC) -I $(LIBFT_INC) $(CC_FLAGS) $< -o $(CD_OBJ_DIR)$@
	@echo "$(COLOR_GREEN)write file: $(CD_OBJ_DIR)$@ $(COLOR_END)"

# Call libft Makefile
$(LIBFT):
	@make -C $(LIBFT_DIR)

test: all
	@./$(BIN_DIR)$(NAME) $(TEST_ARGS)

tleaks: all
	@$(TEST_LEAKS) ./$(BIN_DIR)$(NAME) $(TEST_ARGS)

clean:
	@$(foreach item,$(CLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@$(foreach item,$(FCLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

#TODO retirar .vscode de git
#TODO retirar las funciones libft no utilizadas
