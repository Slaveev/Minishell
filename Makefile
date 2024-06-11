# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 13:38:52 by jsamardz          #+#    #+#              #
#    Updated: 2024/06/11 13:46:58 by jsamardz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c
OBJ = $(SRC:.c=.o) 

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "make"
	@$(CC) $(OBJ) -o $(NAME) -lreadline

clean:
	@echo "clean"
	@rm -f $(OBJ)

fclean: clean
	@echo "fclean"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re