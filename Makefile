# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabelque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 13:38:41 by aabelque          #+#    #+#              #
#    Updated: 2021/10/18 20:27:27 by zizou            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make

H_DIR = include/
C_DIR = src/
O_DIR = objs/

NAME = ft_ping

CC = gcc
DEBUG = -g3
CFLAG = -Wall -Wextra -Werror -Wpadded

SRC = ft_ping.c
SRC += utils.c
SRC += libc.c
SRC += parse_args.c
SRC += init.c
SRC += hostname.c
SRC += send_ping.c
SRC += recv_ping.c

all: $(NAME)

OBJS = $(addprefix $(O_DIR),$(SRC:.c=.o))
	
$(NAME): $(OBJS) $(H_DIR)
	@$(CC) $(DEBUG) $(CFLAGS) -o $(NAME) $(OBJS)
	@tput dl; tput el1; tput cub 100; echo "\033[33mBuilt $(NAME):\033[0m \033[32;1;4m$(notdir $@)\033[0m"

$(OBJS): $(O_DIR)%.o: $(C_DIR)%.c
	@mkdir -p $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $< -fPIC -I$(H_DIR)

clean:
	@rm -rf $(O_DIR) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -rf $(NAME) 2> /dev/null || echo "" > /dev/null
	@echo "\033[33mRemoved ft_nm: \033[32;1;4m$(NAME)\033[0m"

re: fclean all

.PHONY: all clean fclean re
