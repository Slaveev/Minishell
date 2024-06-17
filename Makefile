<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 13:38:52 by jsamardz          #+#    #+#              #
#    Updated: 2024/06/11 15:28:01 by jsamardz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wextra -Werror -Wall -std=c99 -g
SRCS = main.c lexer.c parser.c builtin.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = libft

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling libft"
	@make -C $(LIBFT_DIR)/
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR)/ -lft -lreadline -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Full cleaning"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
>>>>>>> 2ea129e415f2e530d08e7aa235941dbd37f50dd7
