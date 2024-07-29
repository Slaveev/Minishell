/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:26:10 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/29 15:48:03 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../libft/libft.h"

t_tok	*create_token(char *value, int type)
{
	t_tok	*token;

	token = malloc(sizeof(t_tok));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	return (token);
}

void	destroy_token(t_tok *token)
{
	free(token->value);
	free(token);
}

void	destroy_lexer(t_lexer *lexer)
{
	if (lexer->token)
	{
		destroy_token(lexer->token);
		lexer->token = NULL;
	}
}

void	init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->cur_char = input[0];
	lexer->pos = 0;
	lexer->cur_state = STATE_GENERAL;
	lexer->token = NULL;
	lexer->token_count = 0;
}

t_tok	*handle_more(t_lexer *lexer)
{
	t_tok	*token;

	if (lexer->input[lexer->pos + 1] == CHAR_MORE)
	{
		token = create_token("CHAR_DOUBLE_MORE", CHAR_DOUBLE_MORE);
		lexer_advance(lexer);
	}
	else
	{
		token = create_token("CHAR_MORE", CHAR_MORE);
	}
	lexer_advance(lexer);
	return (token);
}

t_tok	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->cur_char != '\0')
	{
		if (lexer->cur_char == CHAR_SPACE)
			handle_space(lexer);
		else if (lexer->cur_char == CHAR_LESS)
			return (handle_less(lexer));
		else if (lexer->cur_char == CHAR_MORE)
			return (handle_more(lexer));
		else if (lexer->cur_char == CHAR_PIPE)
			return (handle_pipe_tok(lexer));
		else if (lexer->cur_char == CHAR_QUOTE)
			return (handle_quote(lexer));
		else if (lexer->cur_char == CHAR_DOUBLE_QUOTE)
			return (handle_double_quote(lexer));
		else if (is_string_identify(lexer->cur_char))
			return (handle_identifier(lexer));
		else if (is_with_dash(lexer->cur_char, lexer->input[lexer->pos + 1]))
			return (handle_dash(lexer));
		else if (lexer->cur_char != CHAR_SPACE)
			return (handle_token_name(lexer));
		else
			lexer_advance(lexer);
	}
	return (NULL);
}
