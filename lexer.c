/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:26:10 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/11 16:25:29 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*create_token(char *value, int type)
{
	t_tok	*token;

	token = malloc(sizeof(t_tok));
	if (!token)
		return (NULL);
	token->value = strdup(value);
	token->type = type;
	return (token);
}

void	destroy_token(t_tok *token)
{
	free(token->value);
	free(token);
}

// init_lexer: This function initializes a lexer with a given input string.
// It sets the initial position, current character, and current state.
void	init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->cur_char = input[0];
	lexer->pos = 0;
	lexer->cur_state = STATE_GENERAL;
	lexer->token = NULL;
	lexer->token_count = 0;
}

// skip_whitespace: This function advances the lexer's position until
// it finds a non-whitespace character.
void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->input[lexer->pos] == CHAR_SPACE)
		lexer->pos++;
}


// advance: This function advances the lexer's position by one and updates the current character.
void	lexer_advance(t_lexer *lexer)
{
	lexer->pos++;
	if (lexer->pos < strlen(lexer->input))
		lexer->cur_char = lexer->input[lexer->pos];
	else
		lexer->cur_char = '\0';
}

// lex_number: This function lexes a number
// from the input string.
t_tok	*lexer_number(t_lexer *lexer)
{
	int		start_pos;
	char	*nbr;
	t_tok	*token;

	start_pos = lexer->pos;
	while (lexer->cur_char >= '0' && lexer->cur_char <= '9')
		lexer_advance(lexer);
	nbr = strndup(lexer->input + start_pos, lexer->pos - start_pos);
	token = create_token(nbr, lexer->token_count);
	return (token);
}

int	is_string_identify(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || ((c >= '0' && c <= '9') || c == '_'));
}
// lex_identifier: This function lexes an
// identifier from the input string.
t_tok	*lexer_identifier(t_lexer *lexer)
{
	int		start_pos;
	char	*ident;
	t_tok	*token;

	start_pos = lexer->pos;
	while (is_string_identify(lexer->cur_char))
		lexer_advance(lexer);
	ident = strndup(lexer->input + start_pos, lexer->pos - start_pos);
	token = create_token(ident, lexer->token_count);
	return (token);
}

int	is_pipe(char c)
{
	return (c == CHAR_PIPE);
}

t_tok	*lexer_pipe(t_lexer *lexer)
{
	t_tok	*token;

	token = create_token("|", lexer->token_count);
	lexer_advance(lexer);
	return (token);
}

int	is_quote(char c)
{
	return (c == CHAR_QUOTE);
}

t_tok	*lexer_quote(t_lexer *lexer)
{
	t_tok	*token;

	token = create_token("\'", lexer->token_count);
	lexer_advance(lexer);
	return (token);
}

int is_double_quote(char c)
{
	return (c == CHAR_DOUBLE_QUOTE);
}

t_tok	*lexer_double_quote(t_lexer *lexer)
{
	t_tok	*token;

	token = create_token("\"", lexer->token_count);
	lexer_advance(lexer);
	return (token);
}

int	is_redirection(char c)
{
	return (c == CHAR_LESS || c == CHAR_MORE);
}

t_tok	*lexer_redirection(t_lexer *lexer)
{
	t_tok	*token;

	token = create_token(&lexer->cur_char, lexer->token_count);
	lexer_advance(lexer);
	return (token);
}

int	is_with_dash(char c, char next_c)
{
	return (c == '-' && ((next_c >= 'a' && next_c <= 'z') || (next_c >= 'A' && next_c <= 'Z')));
}

t_tok	*lexer_dash(t_lexer *lexer)
{
    t_tok	*token;
    int		start_pos;
    char	*ident;

    start_pos = lexer->pos;
    lexer_advance(lexer);
    while ((lexer->cur_char >= 'a' && lexer->cur_char <= 'z') || (lexer->cur_char >= 'A' && lexer->cur_char <= 'Z'))
        lexer_advance(lexer);

    ident = strndup(lexer->input + start_pos, lexer->pos - start_pos);
    token = create_token(ident, lexer->token_count);
    return (token);
}

// lex_string: This function lexes a string from the input string.

// next_token: This function returns the next token from the input string.
// It uses the other lexing functions to recognize the type of the next token and lex it.
t_tok	*lexer_get_next_token(t_lexer *lexer)
{
	t_tok	*token;

	while (lexer->cur_char != '\0')
	{
		if (lexer->cur_char == CHAR_SPACE || lexer->cur_char == '\0')
		{
			lexer_advance(lexer);
			// return NULL;
		}
		else if (lexer->cur_char >= '0' && lexer->cur_char <= '9')
		{
			token = lexer_number(lexer);
			return (token);
		}
		else if (is_string_identify(lexer->cur_char))
		{
			token = lexer_identifier(lexer);
			return (token);
		}
		else if (is_pipe(lexer->cur_char))
		{
			token = lexer_pipe(lexer);
			return (token);
		}
		else if (is_quote(lexer->cur_char))
		{
    		token = lexer_quote(lexer);
			return (token);
		}
		else if (is_double_quote(lexer->cur_char))
		{
			token = lexer_double_quote(lexer);
			return (token);
		}
		else if (is_redirection(lexer->cur_char))
		{
			token = lexer_redirection(lexer);
			return (token);
		}
		else if (is_with_dash(lexer->cur_char, lexer->input[lexer->pos + 1]))
		{
			token = lexer_dash(lexer);
			return (token);
		}
		else
		{
			lexer_advance(lexer);
			continue;
		}
	}
	return (0);
}

// << < > >> | ' '
