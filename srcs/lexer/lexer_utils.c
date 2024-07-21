/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:13:47 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 14:27:53 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

char	*strip_quotes(char *str)
{
	int	i;

	i = strlen(str);
	if (str[0] == '"' && str[i - 1] == '"')
	{
		str[i - 1] = '\0';
		return (str + 1);
	}
	else if (str[0] == '\'' && str[i - 1] == '\'')
	{
		str[i - 1] = '\0';
		return (str + 1);
	}
	return (str);
}

int	is_with_dash(char c, char next_c)
{
	return (c == '-' && ((next_c >= 'a' && next_c <= 'z')
			|| (next_c >= 'A' && next_c <= 'Z')));
}

t_tok	*lexer_dash(t_lexer *lexer)
{
	t_tok	*token;
	int		start_pos;
	char	*ident;

	start_pos = lexer->pos;
	lexer_advance(lexer);
	while ((lexer->cur_char >= 'a' && lexer->cur_char <= 'z')
		|| (lexer->cur_char >= 'A' && lexer->cur_char <= 'Z')
		|| lexer->cur_char == '-')
		lexer_advance(lexer);
	ident = strndup(lexer->input + start_pos, lexer->pos - start_pos);
	token = create_token(ident, WORD);
	return (token);
}

t_tok	*lexer_token_name(t_lexer *lexer)
{
	int		start_pos;
	char	*word;
	t_tok	*token;

	start_pos = lexer->pos;
	while (lexer->cur_char != CHAR_SPACE && lexer->cur_char != '\0')
		lexer_advance(lexer);
	word = strndup(lexer->input + start_pos, lexer->pos - start_pos);
	token = create_token(word, WORD);
	return (token);
}

t_tok	*process_token(t_lexer *lexer, char end_char, int token_type,
					int quotes)
{
	int		start_pos;
	char	*ident;
	t_tok	*token;

	lexer_advance(lexer);
	start_pos = lexer->pos;
	while (lexer->cur_char != end_char && lexer->cur_char != '\0')
		lexer_advance(lexer);
	ident = strndup(lexer->input + start_pos, lexer->pos - start_pos);
	if (quotes)
		ident = strip_quotes(ident);
	token = create_token(ident, token_type);
	lexer_advance(lexer);
	return (token);
}
