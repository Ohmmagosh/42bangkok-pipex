# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 21:05:48 by psuanpro          #+#    #+#              #
#    Updated: 2022/08/03 15:01:49 by psuanpro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = *.c
OBJS = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
	rm -rf heredoc outfile


re: fclean all

test1:re
	@./pipex infile "grep qw" "wc -w" outfile
	@echo "------ft_pipex------"
	@cat outfile
	@echo "------system------"
	@cat infile | grep qw | wc -w

tester1:re
	@echo "------wrong file------"
	@./pipex infileewew "grep qw" "wc -w" outfile
	@cato

tester2:re
	@echo "------wrong input------"
	@./pipex infile "grep qw" outfile

tester3:re
	@echo "------wrong command------"
	@./pipex infile "grep qw" "wc -/l" outfile


hdoc:re
	./pipex here_doc EOF "cat" "wc -l" outfile
	cat outfile

chkl:re
	valgrind --leak-check=full ./pipex infile "grep qw" "wc -w" outfile 

.PHONY: all clean fclean re test1 tester1 tester2 tester3 cat1 hdoc