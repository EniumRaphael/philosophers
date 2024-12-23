# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 11:05:05 by rparodi           #+#    #+#              #
#    Updated: 2024/07/24 14:12:44 by rparodi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Variables

# Name
NAME = philo

# Commands
CC = cc
RM = rm -rf

# Flags
CFLAGS = -Werror -Wextra -Wall -Wno-unused-command-line-argument -g3 -MMD

# CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=thread

INCLUDES =	./includes/philo.h \
			./includes/types.h

SRC =	./sources/ft_atou.c \
		./sources/ft_exit.c \
		./sources/main.c \
		./sources/parsing_args.c \
		./sources/routine.c \
		./sources/ft_actions.c

# Objects
OBJDIRNAME = ./objects
OBJ = $(addprefix $(OBJDIRNAME)/,$(SRC:.c=.o))

# Colors
GREEN = \033[32m
GREY = \033[0;90m
RED = \033[0;31m
GOLD = \033[38;5;220m
END = \033[0m

# Rules

# All (make all)
all: header $(NAME) footer

# Bonus (make bonus)
bonus: header $(OBJ) $(LIB_OBJ) footer
	@mkdir -p $(OBJDIRNAME)
	@mkdir -p $(OBJDIRNAME)/$(SRCDIRNAME)
	@printf '$(GREY) Creating $(END)$(GREEN)$(OBJDIRNAME)$(END)\n'
	@printf '$(GREY) Be Carefull ur in $(END)$(GREEN)Debug Mode$(END)\n'
	@cc $(CFLAGS) -D DEBUG=42 -o $(NAME) $(OBJ) $(LIB_OBJ)

# Clean (make clean)
clean:
	@printf '$(GREY) Removing $(END)$(RED)Objects$(END)\n'
	@printf '$(GREY) Removing $(END)$(RED)Objects Folder$(END)\n'
	@$(RM) $(OBJDIRNAME)

# Clean (make fclean)
fclean: clean
	@printf '$(GREY) Removing $(END)$(RED)Program$(END)\n'
	@$(RM) $(NAME)
	@echo ""

# Restart (make re)
re: header fclean all

# Dependences for all
$(NAME): $(OBJ)
	@mkdir -p $(OBJDIRNAME)
	@mkdir -p $(OBJDIRNAME)/$(SRCDIRNAME)
	@printf '$(GREY) Creating $(END)$(GREEN)$(OBJDIRNAME)$(END)\n'
	@cc $(CFLAGS) -o $(NAME) $(OBJ)

# Creating the objects
$(OBJDIRNAME)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf '$(GREY) Compiling $(END)$(GREEN)$<$(END)\n'
	@cc $(CFLAGS) -o $@ -c $<

#	Header
header:
		@clear
		@printf '\n\n'
		@printf '$(GOLD)            *******     ****** ******* $(END)\n'
		@printf '$(GOLD)          ******        ***    ******* $(END)\n'
		@printf '$(GOLD)      *******           *      ******* $(END)\n'
		@printf '$(GOLD)     ******                  ******* $(END)\n'
		@printf '$(GOLD)  *******                  ******* $(END)\n'
		@printf '$(GOLD) *******************    *******      * $(END)\n'
		@printf '$(GOLD) *******************    *******    *** $(END)\n'
		@printf '$(GOLD)              ******    ******* ****** $(END)\n'
		@printf '$(GOLD)              ******  $(END)\n'
		@printf '$(GOLD)              ******  $(END)\n'
		@printf '$(GREY)                                      Made by rparodi$(END)\n\n'

#	Footer
footer:
		@printf "\n"
		@printf "$(GOLD)                   ,_     _,$(END)\n"
		@printf "$(GOLD)                   | \\___//|$(END)\n"
		@printf "$(GOLD)                   |=6   6=|$(END)\n"
		@printf "$(GOLD)                   \\=._Y_.=/$(END)\n"
		@printf "$(GOLD)                    )  \`  (    ,$(END)\n"
		@printf "$(GOLD)                   /       \\  (('$(END)\n"
		@printf "$(GOLD)                   |       |   ))$(END)\n"
		@printf "$(GOLD)                  /| |   | |\\_//$(END)\n"
		@printf "$(GOLD)                  \\| |._.| |/-\`$(END)\n"
		@printf "$(GOLD)                   '\"'   '\"'$(END)\n"
		@printf '              $(GREY)The compilation is$(END) $(GOLD)finish$(END)\n               $(GREY)Have a good $(END)$(GOLD)correction !$(END)\n'

#	Phony
.PHONY: all bonus clean fclean re

-include	${OBJ:.o=.d}
