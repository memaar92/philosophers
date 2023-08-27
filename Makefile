# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/26 11:54:25 by mamesser          #+#    #+#              #
#    Updated: 2023/08/26 11:55:49 by mamesser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c

OBJS := $(SRCS:%.c=%.o)

# HEADERS = push_swap.h

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $@

%.o: %.c $(HEADERS)
	cc $(CFLAGS) -I. -c $< -o $@

bonus: all

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all
