# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 21:05:48 by psuanpro          #+#    #+#              #
#    Updated: 2022/08/07 23:57:29 by psuanpro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c\
	pipex_utils.c\
	pipex_utils_1.c\
	get_next_line_utils.c\
	get_next_line.c\
	ft_strncmp.c\
	ft_strlen.c\
	ft_strlcpy.c\
	ft_strjoin.c\
	ft_split.c\

OBJS = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
	rm -rf here_doc outfile

re: fclean all

.PHONY: all clean fclean re 