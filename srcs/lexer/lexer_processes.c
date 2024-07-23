/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:03:11 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/22 12:03:27 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tok	*handle_quote(t_lexer *lexer)
{
	return (process_token(lexer, CHAR_QUOTE, WORD, 1));
}

t_tok	*handle_double_quote(t_lexer *lexer)
{
	return (process_token(lexer, CHAR_DOUBLE_QUOTE, WORD, 1));
}

t_tok	*handle_identifier(t_lexer *lexer)
{
	return (lexer_identifier(lexer));
}

t_tok	*handle_dash(t_lexer *lexer)
{
	return (lexer_dash(lexer));
}

t_tok	*handle_token_name(t_lexer *lexer)
{
	return (lexer_token_name(lexer));
}