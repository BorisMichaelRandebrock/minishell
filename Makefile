# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 17:53:17 by fmontser          #+#    #+#              #
#    Updated: 2024/05/20 12:32:22 by fmontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 		+= --silent
MAKEFILE		:= Makefile

INC_DIR			:= include/
SRC_DIR			:= src/ src/__builtin
OBJ_DIR			:= obj/
BIN_DIR			:= bin/
NAME			:= minishell
HDRS 			:= minishell.h
SRCS 			:=	main.c shell.c environment.c memutils.c tokenization.c\
					expansion.c validation.c fileutils.c dirutils.c pipeline.c\
					exception.c execution.c heredoc.c signal.c command.c\
					cleanutils.c cleanutils2.c builtin.c redirs.c\
					__echo.c __export.c __env.c __unset.c __pwd.c __exit.c\
					__cd.c

OBJS			:= $(SRCS:.c=.o)

LIBFT_DIR		:= src/libft
LIBFT_INC		:= src/libft/include
LIBFT			:= src/libft/lib/libft.a

LIBRL_DIR		:= src/readline
LIBRL_INC		:= src/readline/include/readline
LIBRL			:= src/readline/lib

CC				:= gcc
PERF_FLAGS		:= #-O3
CC_FLAGS		:= -Wall -Werror -Wextra -g -c $(PERF_FLAGS) -D READLINE_LIBRARY=READLINE_LIBRARY
STD_LIBS		:= -lreadline -ltermcap
TEST_LEAKS		:= leaks -atExit --

CLEAN_TARGETS	= $(wildcard $(addprefix $(OBJ_DIR), $(OBJS)))
FCLEAN_TARGETS	= $(wildcard $(addprefix $(BIN_DIR), $(NAME)))

COLOR_GREEN		:=\033[0;32m
COLOR_RED		:=\033[0;31m
COLOR_BLUE		:=\033[0;34m
COLOR_END		:=\033[0m

vpath %.h $(INC_DIR) $(LIBFT_INC)
vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
vpath % $(BIN_DIR)

all: $(NAME) $(LIBFT) $(LIBRL)

$(NAME): $(OBJS) $(LIBFT) $(LIBRL)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(addprefix $(OBJ_DIR),$(OBJS)) $(LIBFT) -o $(BIN_DIR)$(NAME) $(STD_LIBS) -L$(LIBRL)
	@echo "$(COLOR_GREEN)write file: $(BIN_DIR)$@ $(COLOR_END)"

%.o : %.c $(HDRS) $(MAKEFILE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -I $(INC_DIR) -I $(LIBFT_INC) -I $(LIBRL_INC) $(CC_FLAGS) $< -o $(OBJ_DIR)$@
	@echo "$(COLOR_GREEN)write file: $(OBJ_DIR)$@ $(COLOR_END)"

$(LIBFT):
	@echo "$(COLOR_BLUE)Compiling libft...$(COLOR_END)"
	@make -C $(LIBFT_DIR)

$(LIBRL):
	@echo "$(COLOR_BLUE)Compiling readline library...$(COLOR_END)"
	@make -C $(LIBRL_DIR)
	@echo "$(COLOR_BLUE)Installing readline library...$(COLOR_END)"
	@make install -C $(LIBRL_DIR)

configure:
	@echo "$(COLOR_BLUE)Configuring readline library...$(COLOR_END)"
	@rm -rf src/readline
	@tar -xvf res/readline-8.2.tar.gz && mv readline-8.2 src/readline
	@cd $(CURDIR)/$(LIBRL_DIR) && ./configure --prefix=$(CURDIR)/$(LIBRL_DIR) --with-curses

test: all
	@./$(BIN_DIR)$(NAME) $(TEST_ARGS)

tleaks: all
	@$(TEST_LEAKS) ./$(BIN_DIR)$(NAME) $(TEST_ARGS)

clean:
	@$(foreach item,$(CLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBRL_DIR)

fclean: clean
	@$(foreach item,$(FCLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(LIBRL_DIR)

purge: fclean
	@rm -rf src/readline
	@echo "$(COLOR_RED)purge dir: src/readline$(COLOR_END)"

re: fclean all

.PHONY: all clean fclean re

#TODO CLEAN retirar .vscode de git
