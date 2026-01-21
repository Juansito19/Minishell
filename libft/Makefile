# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 16:44:12 by Juan              #+#    #+#              #
#    Updated: 2026/01/19 12:34:36 by jbrosio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Var to compilator
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

## Var to files ft
SRC = src/ft_atod.c \
		src/ft_atoi.c \
		src/ft_atol.c \
		src/ft_bzero.c \
		src/ft_calloc.c \
		src/ft_dblstr_join.c \
		src/ft_double_free.c \
		src/ft_double_putstr.c \
		src/ft_free_nodes.c \
		src/ft_hex_control.c \
		src/ft_hex_control_fd.c \
		src/ft_isalnum.c \
		src/ft_isalpha.c \
		src/ft_isascii.c \
		src/ft_isspace.c \
		src/ft_isdigit.c \
		src/ft_isprint.c \
		src/ft_itoa.c \
		src/ft_lstadd_back.c \
		src/ft_lstadd_front.c \
		src/ft_lstclear.c \
		src/ft_lstdelone.c \
		src/ft_lstiter.c \
		src/ft_lstlast.c \
		src/ft_lstmap.c \
		src/ft_lstnew.c \
		src/ft_lstsize.c \
		src/ft_memchr.c \
		src/ft_memcmp.c \
		src/ft_memcpy.c \
		src/ft_memmove.c \
		src/ft_memset.c \
		src/ft_printf.c \
		src/ft_fprintf.c \
		src/ft_putchar_fd.c \
		src/ft_putendl_fd.c \
		src/ft_putnbr_fd.c \
		src/ft_putnbr_u.c \
		src/ft_putnbr_u_fd.c \
		src/ft_putstr_fd.c \
		src/ft_searchtype.c \
		src/ft_searchtype_fd.c \
		src/ft_split.c \
		src/ft_strchr.c \
		src/ft_strdup.c \
		src/ft_array_dup.c \
		src/ft_striteri.c \
		src/ft_strjoin.c \
		src/ft_strlcat.c \
		src/ft_strlcpy.c \
		src/ft_strlen.c \
		src/ft_strmapi.c \
		src/ft_strncmp.c \
		src/ft_strcmp.c \
		src/ft_strnstr.c \
		src/ft_strrchr.c \
		src/ft_strtrim.c \
		src/ft_substr.c \
		src/ft_tolower.c \
		src/ft_toupper.c \
		src/ft_sort_int_tab.c \
		src/get_next_line.c \
		src/get_next_line_utils.c

OBJ = $(SRC:src/%.c=obj/%.o)

TOTAL_FILES := $(words $(SRC))
COMPILED := 0

## Rules
all: $(NAME)

## compile rule
run:
	@$(CC) $(CFLAGS) $(SRC) && ./a.out

## converting .c to .o
obj/%.o: src/%.c
	@sleep 0.01
	@mkdir -p obj
	@$(CC) $(CFLAGS) -fPIC -c $< -o $@
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@$(eval PROGRESS=$(shell echo $$(($(COMPILED)*50/$(TOTAL_FILES)))))
	@printf "\r\e[32mLIBFT = [%-50s] %d/%d files\e[0m" \
		$$(printf '█%.0s' $$(seq 1 $(PROGRESS))) $(COMPILED) $(TOTAL_FILES)

## library
$(NAME) : $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "\e[32m    \e[0m"
	@echo "\e[32m    \e[0m"
	@echo "\e[32m    \e[0m"
	@sleep 0.08
	@echo "\e[32m    \e[0m"
	@sleep 0.08
	@sleep 0.08
	@echo "\e[32m               ███████████████ ███████████   █████████ ███████████ █████ █████            \e[0m"
	@sleep 0.08
	@echo "\e[32m   ░░███     ░░██░░███░░░░░██░░███░░░░░███ ███░░░░░██░░███░░░░░██░░███ ░░███             \e[0m"
	@sleep 0.08
	@echo "\e[32m    ░███      ░███░███    ░███░███    ░███░███    ░███░███    ░███░░███ ███              \e[0m"
	@sleep 0.08
	@echo "\e[32m    ░███      ░███░██████████ ░██████████ ░███████████░██████████  ░░█████               \e[0m"
	@sleep 0.08
	@echo "\e[32m    ░███      ░███░███░░░░░███░███░░░░░███░███░░░░░███░███░░░░░███  ░░███                \e[0m"
	@sleep 0.08
	@echo "\e[32m    ░███      ░███░███    ░███░███    ░███░███    ░███░███    ░███   ░███                \e[0m"
	@sleep 0.08
	@echo "\e[32m    █████████████████████████ █████   █████████   █████████   █████  █████               \e[0m"
	@sleep 0.08
	@echo "\e[32m   ░░░░░░░░░░░░░░░░░░░░░░░░░ ░░░░░   ░░░░░░░░░   ░░░░░░░░░   ░░░░░  ░░░░░                \e[0m"
	@sleep 0.08
	@echo "\e[32m   \e[0m"
	@sleep 0.08
	@echo "\e[32m   \e[0m"
	@sleep 0.08
	@echo "\e[32m   \e[0m"
	@sleep 0.08
	@echo "\e[32m      █████████ ███████████ ██████████ █████████ ███████████████████████████████      ███\e[0m"
	@sleep 0.08
	@echo "\e[32m     ███░░░░░██░░███░░░░░██░░███░░░░░████░░░░░██░█░░░███░░░░░███░░░░░░░███░░░░███    ░███\e[0m"
	@sleep 0.08
	@echo "\e[32m    ███     ░░░ ░███    ░███░███  █ ░░███    ░██░   ░███  ░ ░███  █ ░ ░███   ░░███   ░███\e[0m"
	@sleep 0.08
	@echo "\e[32m   ░███         ░██████████ ░██████  ░███████████   ░███    ░██████   ░███    ░███   ░███\e[0m"
	@sleep 0.08
	@echo "\e[32m   ░███         ░███░░░░░███░███░░█  ░███░░░░░███   ░███    ░███░░█   ░███    ░███   ░███\e[0m"
	@sleep 0.08
	@echo "\e[32m   ░░███     ███░███    ░███░███ ░   ░███    ░███   ░███    ░███ ░   █░███    ███    ░░░ \e[0m"
	@sleep 0.08
	@echo "\e[32m    ░░█████████ █████   ██████████████████   █████  █████   ████████████████████      ███\e[0m"
	@sleep 0.08
	@echo "\e[32m     ░░░░░░░░░ ░░░░░   ░░░░░░░░░░░░░░░░░░   ░░░░░  ░░░░░   ░░░░░░░░░░░░░░░░░░░░      ░░░ \e[0m"
	@sleep 0.08
	@echo "\e[32m   \e[0m"
	@sleep 0.08
	@echo "\e[32m   \e[0m"
	@sleep 0.08
	@echo "\e[32m   \e[0m"
	@sleep 0.08
	@sleep 1

## Remove rules
clean:
	@$(RM) obj

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
