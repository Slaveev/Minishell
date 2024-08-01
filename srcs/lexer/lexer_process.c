/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:02:09 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/22 12:02:55 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tok	*handle_char_more(t_lexer *lexer)
{
	if (lexer->input[lexer->pos + 1] == CHAR_MORE)
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (create_token("CHAR_DOUBLE_MORE", CHAR_DOUBLE_MORE));
	}
	else
	{
		lexer_advance(lexer);
		return (create_token("CHAR_MORE", CHAR_MORE));
	}
}

t_tok	*handle_space(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (NULL);
}

t_tok	*handle_less(t_lexer *lexer)
{
	t_tok	*token;

	token = create_token("CHAR_LESS", CHAR_LESS);
	lexer_advance(lexer);
	return (token);
}

t_tok	*handle_pipe_tok(t_lexer *lexer)
{
	return (lexer_pipe(lexer));
}

t_tok	*handle_open_paren(t_lexer *lexer)
{
	return (process_token(lexer, '(', COMMAND_GROUP, 0));
}
