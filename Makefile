# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/26 11:54:25 by mamesser          #+#    #+#              #
#    Updated: 2023/09/21 10:42:16 by mamesser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread

DFLAGS = -fsanitize=thread -g

SRCS_DIR = ./sources/

SRCS = $(addprefix $(SRCS_DIR),main.c init_structs.c utils.c utils2.c events.c timing.c threading.c free_mem.c)

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(SRCS_DIR)%.o)

HEADERS = ./includes/philo.h

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	cc $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all
