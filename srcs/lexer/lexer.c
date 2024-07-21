/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:26:10 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 14:27:32 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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

void	init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->cur_char = input[0];
	lexer->pos = 0;
	lexer->cur_state = STATE_GENERAL;
	lexer->token = NULL;
	lexer->token_count = 0;
}

t_tok	*lexer_get_next_token(t_lexer *lexer)
{
	t_tok	*token;

	token = NULL;
	while (lexer->cur_char != '\0')
	{
		switch (lexer->cur_char)
		{
			case CHAR_SPACE:
				lexer_advance(lexer);
				break;
			case CHAR_LESS:
				token = create_token("CHAR_LESS", CHAR_LESS);
				lexer_advance(lexer);
				return (token);
			case CHAR_MORE:
				if (lexer->input[lexer->pos + 1] == CHAR_MORE)
				{
					token = create_token("CHAR_DOUBLE_MORE", CHAR_DOUBLE_MORE);
					lexer_advance(lexer);
				}
				else
					token = create_token("CHAR_MORE", CHAR_MORE);
				lexer_advance(lexer);
				return (token);
			case CHAR_PIPE:
				return ((token = lexer_pipe(lexer), token));
			case '(':
				return (process_token(lexer, '(', COMMAND_GROUP, 0));
			case CHAR_QUOTE:
				return (process_token(lexer, CHAR_QUOTE, WORD, 1));
			case CHAR_DOUBLE_QUOTE:
				return (process_token(lexer, CHAR_DOUBLE_QUOTE, WORD, 1));
			default :
				if (is_string_identify(lexer->cur_char))
					return ((token = lexer_identifier(lexer)), token);
				else if (is_with_dash(lexer->cur_char, lexer->input[lexer->pos + 1]))
					return ((token = lexer_dash(lexer)), token);
				else if (lexer->cur_char != CHAR_SPACE)
					return ((token = lexer_token_name(lexer)), token);
				else
					lexer_advance(lexer);
				break ;
		}
	}
	return (NULL);
}
