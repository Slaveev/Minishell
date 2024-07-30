NAME = minishell
CC = cc
CFLAGS = -Wextra -Werror -Wall -std=c99 -g

# Subdirectories
SRC_DIR = srcs
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXEC_DIR = $(SRC_DIR)/exec
BUILTIN_DIR = $(SRC_DIR)/builtin
SIGNALS_DIR = $(SRC_DIR)/signals
UTILS_DIR = $(SRC_DIR)/utils
ENVIRON_DIR = $(SRC_DIR)/environ
HEREDOC_DIR = $(SRC_DIR)/heredoc
REDIR_DIR = $(SRC_DIR)/redir
FREE_DIR = $(SRC_DIR)/free

# Source files
SRCS = main.c \
		$(LEXER_DIR)/lexer.c $(LEXER_DIR)/lexer_helper.c $(LEXER_DIR)/lexer_utils.c \
		$(PARSER_DIR)/parser.c $(PARSER_DIR)/parser_init.c \
		$(BUILTIN_DIR)/builtin.c $(SIGNALS_DIR)/signals.c $(EXEC_DIR)/exec.c \
		$(UTILS_DIR)/utils.c $(ENVIRON_DIR)/env.c $(EXEC_DIR)/exec_utils.c \
		$(REDIR_DIR)/redir.c $(HEREDOC_DIR)/heredoc.c $(FREE_DIR)/free.c \
		$(ENVIRON_DIR)/env_help.c $(BUILTIN_DIR)/builtins_utils.c \
		$(UTILS_DIR)/utils1.c  $(PARSER_DIR)/parser_utils.c\
		$(LEXER_DIR)/lexer_process.c $(LEXER_DIR)/lexer_processes.c \
		$(FREE_DIR)/free2.c $(FREE_DIR)/free3.c

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
