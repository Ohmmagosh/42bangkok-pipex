# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 21:05:48 by psuanpro          #+#    #+#              #
#    Updated: 2022/07/14 11:26:25 by psuanpro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = *.c
OBJS = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
clean:
	rm -rf $(OBJS)
fclean: clean
	rm-rf $(NAME)
re: fclean all

.PHONY: all clean fclean re