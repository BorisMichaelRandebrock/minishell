# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 14:35:42 by fmontser          #+#    #+#              #
#    Updated: 2024/03/22 22:50:18 by fmontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 		+= --silent
MAKEFILE		:= Makefile

ROOT_DIR		:= $(CURDIR)/
INC_DIR			:= include/
SRC_DIR			:= src/
OBJ_DIR			:= obj/
LIB_DIR			:= lib/
BIN_DIR			:= bin/
BIN_NAME		:= program
NAME			:= libfm.a
HDRS 			:= fm_lib.h fm_alloc.h fm_list.h
SRCS 			:= fm_alloc.c fm_list.c fm_list_free.c #main.c

OBJS 			:= $(SRCS:%.c=%.o)
LIBS 			:= libfm.a

W_FLAGS			:= -Wall -Werror -Wextra
CC_FLAGS 		:= $(W_FLAGS) -g -c

CLEAN_TARGETS = $(wildcard $(addprefix $(OBJ_DIR),$(OBJS)))
FCLEAN_TARGETS = $(wildcard $(addprefix $(LIB_DIR),$(LIBS))) $(wildcard $(addprefix $(BIN_DIR),$(BIN_NAME)))

COLOR_GREEN :=\033[0;32m
COLOR_RED	:=\033[0;31m
COLOR_BLUE	:=\033[0;34m
COLOR_END	:=\033[0m

vpath %.h $(INC_DIR)
vpath %.c $(SRC_DIR) $(ROOT_DIR)
vpath %.o $(OBJ_DIR)
vpath %.a $(LIB_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB_DIR)$(NAME) $(addprefix $(OBJ_DIR),$(OBJS))
	@echo "$(COLOR_GREEN)write file: $(LIB_DIR)$@ $(COLOR_END)"

%.o : %.c $(HDRS) $(MAKEFILE)
	@mkdir -p $(OBJ_DIR)
	@gcc -I $(INC_DIR) $(CC_FLAGS) $< -o $(OBJ_DIR)$@
	@echo "$(COLOR_GREEN)write file: $(OBJ_DIR)$@ $(COLOR_END)"


test: $(NAME)
	@mkdir -p $(BIN_DIR)
	@gcc -g $(WFLAGS) $(LIB_DIR)$(NAME) -o $(BIN_DIR)$(BIN_NAME) && ./$(BIN_DIR)$(BIN_NAME) && rm -rf *dSYM*

tleaks: $(NAME)
	@mkdir -p $(BIN_DIR)
	@gcc -g $(WFLAGS) $(LIB_DIR)$(NAME) -o $(BIN_DIR)$(BIN_NAME) && leaks -atExit -- ./$(BIN_DIR)$(BIN_NAME) && rm -rf *dSYM*

tbuild: $(NAME)
	@mkdir -p $(BIN_DIR)
	@gcc -g $(WFLAGS) $(LIB_DIR)$(NAME) -o $(BIN_DIR)$(BIN_NAME) && rm -rf *dSYM*

clean:
	@$(foreach item,$(CLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)

fclean: clean
	@$(foreach item,$(FCLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)

re: fclean all

.PHONY: all clean fclean re
