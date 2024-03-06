# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 11:01:16 by fmontser          #+#    #+#              #
#    Updated: 2024/03/05 23:02:41 by fmontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 		+= --silent
MAKEFILE		:= Makefile

INC_DIR			:= include/
SRC_DIR			:= src/
OBJ_DIR			:= obj/
LIB_DIR			:= lib/
NAME 			:= libft.a
HDRS 			:= libft.h
SRCS 			:= ft_atoi.c ft_bzero.c ft_calloc.c ft_free_list.c ft_is_prime.c\
ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c\
ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c\
ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_realloc.c ft_split.c\
ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strrev.c ft_strtrim.c ft_substr.c\
ft_tolower.c ft_toupper.c ft_utoa.c ft_utox.c ft_fload.c ft_fexists.c ft_fsize.c ft_is_whspc.c\

OBJS 			:= $(SRCS:%.c=%.o)
LIBS 			:= libft.a

CC_FLAGS 		:= -Wall -Werror -Wextra -g -c

CLEAN_TARGETS = $(wildcard $(addprefix $(OBJ_DIR),$(OBJS)))
FCLEAN_TARGETS = $(wildcard $(addprefix $(LIB_DIR),$(LIBS)))

COLOR_GREEN :=\033[0;32m
COLOR_RED	:=\033[0;31m
COLOR_BLUE	:=\033[0;34m
COLOR_END	:=\033[0m

vpath %.h $(INC_DIR)
vpath %.c $(SRC_DIR)
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

clean:
	@$(foreach item,$(CLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)

fclean: clean
	@$(foreach item,$(FCLEAN_TARGETS),echo "$(COLOR_RED)delete file: $(item)$(COLOR_END)"; rm $(item);)

re: fclean all

.PHONY: all clean fclean re
