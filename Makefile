# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/26 11:54:25 by mamesser          #+#    #+#              #
#    Updated: 2023/09/02 14:46:39 by mamesser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = ./sources/

SRCS = $(addprefix $(SRCS_DIR),main.c init_structs.c utils.c)

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(SRCS_DIR)%.o)

# HEADERS = push_swap.h

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $@

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	cc $(CFLAGS) -I. -c $< -o $@

bonus: all

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all
