/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:33:42 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/19 14:19:10 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
// # include "minishell.h"

enum e_token_types{
	CHAR_DOUBLE_MORE = 256,
	CHAR_LESS = '<',
	CHAR_MORE = '>',
	CHAR_PIPE = '|',
	CHAR_SEMICOLON = ';',
	CHAR_SPACE = ' ',
	CHAR_QUOTE = '\'',
	CHAR_DOUBLE_QUOTE = '\"',
	CHAR_BACKSLASH = '\\',
	CHAR_DOLLAR = '$',
	CHAR_AMPERSAND = '&',
	CHAR_UNDESCP = '`',
	CHAR_BRACKET_O = '(',
	CHAR_BRACKET_C = ')',
	WORD,
	NUMBER,
	COMMAND_GROUP,
	ARGUMENT,
	COMMAND
};

enum e_state {
	STATE_GENERAL,
	STATE_QUOTE,
	STATE_DOUBLE_QUOTE,
};

typedef struct s_tok
{
	char	*value;
	int		type;
	int		count;
}			t_tok;

typedef struct s_lexer
{
	t_tok			*token;
	int				token_count;
	char			*input;
	char			cur_char;
	int				pos;
	enum e_state	cur_state;
}					t_lexer;

char	*strip_quotes(char *str);
void	init_lexer(t_lexer *lexer, char *input);
t_tok	*create_token(char *value, int type);
int		is_string_identify(char c);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
t_tok	*lexer_get_next_token(t_lexer *lexer);
t_tok	*lexer_number(t_lexer *lexer);
t_tok	*lexer_identifier(t_lexer *lexer);
int		is_pipe(char c);
t_tok	*lexer_pipe(t_lexer *lexer);
int		is_quote(char c);
t_tok	*lexer_quote(t_lexer *lexer);
int		is_double_quote(char c);
t_tok	*lexer_double_quote(t_lexer *lexer);
int		is_redirection(char c);
t_tok	*lexer_redirection(t_lexer *lexer);
void	destroy_token(t_tok *token);

int		is_with_dash(char c, char next_c);
t_tok	*lexer_dash(t_lexer *lexer);
t_tok	*lexer_token_name(t_lexer *lexer);
t_tok	*process_token(t_lexer *lexer, char end_char,
			int token_type, int quotes);

#endif
