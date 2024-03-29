# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 17:53:17 by fmontser          #+#    #+#              #
#    Updated: 2024/03/21 11:45:47 by fmontser         ###   ########.fr        #
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
SRCS 			:=	main.c shell.c enviorment.c memutils.c tokenizer.c expander.c \
					pipeline.c redirs.c exception.c free.c \
					__echo.c __env.c __export.c __unset.c __pwd.c __exit.c __cd.c \
					__history.c

OBJS			:= $(SRCS:.c=.o)

LIBFT_DIR		:= src/libft/
LIBFT_INC		:= src/libft/include
LIBFT			:= src/libft/lib/libft.a

CC				:= gcc
PERF_FLAGS		:= #-O3
CC_FLAGS		:= -Wall -Werror -Wextra -g -c $(PERF_FLAGS)
STD_LIBS		:= -lreadline
TEST_LEAKS		:= leaks -atExit --
TEST_VLEAKS		:= valgrind --show-error-list=no  --trace-children=no

CLEAN_TARGETS	=	$(wildcard $(addprefix $(OBJ_DIR), $(OBJS)))
FCLEAN_TARGETS	= $(wildcard $(addprefix $(BIN_DIR), $(NAME)))

COLOR_GREEN		:=\033[0;32m
COLOR_RED		:=\033[0;31m
COLOR_BLUE		:=\033[0;34m
COLOR_END		:=\033[0m

vpath %.h $(INC_DIR) $(LIBFT_INC)
vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
vpath % $(BIN_DIR)

all: $(NAME) $(LIBFT)

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

# Call libft Makefile
$(LIBFT):
	@make -C $(LIBFT_DIR)

test: all
	@./$(BIN_DIR)$(NAME) $(TEST_ARGS)

tleaks: all
	@$(TEST_LEAKS) ./$(BIN_DIR)$(NAME) $(TEST_ARGS)

tvleaks: all
	@$(TEST_VLEAKS) ./$(BIN_DIR)$(NAME) $(TEST_ARGS)

clean:
	@$(foreach item,$(CLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@$(foreach item,$(FCLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

#TODO probar a pasar argumentos a minishell ej. ls | ./minishell... no debe petar!
#TODO	set_evar("_=", cmd->tkn->str); para procesos!!!
#TODO repasar tema del history, es mas complejo...mirar bash manual
#TODO la gestion de memoria es valida pero no me convence...
#TODO ft_strjoin, ft_strlen, ft_strnstr, ft_is_whspc update(fran),  ft_rszarray, libft.h, makefile
#TODO limpieza includes
#TODO retirar .vscode de git
#TODO retirar las funciones libft no utilizadas
#TODO resolver que pasa cuando no se recompilan slos cambios de una libreria o make anidado

