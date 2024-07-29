/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:12:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/29 12:11:42 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../libft/libft.h"

int	get_token_type(char *value)
{
	if (!strcmp(value, "<"))
		return (CHAR_LESS);
	else if (!strcmp(value, ">"))
		return (CHAR_MORE);
	else if (!strcmp(value, ">>"))
		return (CHAR_DOUBLE_MORE);
	else if (!strcmp(value, "|"))
		return (CHAR_PIPE);
	else if (!strcmp(value, " "))
		return (CHAR_SPACE);
	else if (!strcmp(value, "\'"))
		return (CHAR_QUOTE);
	else if (!strcmp(value, "\""))
		return (CHAR_DOUBLE_QUOTE);
	else if (!strcmp(value, "\\"))
		return (CHAR_BACKSLASH);
	else if (!strcmp(value, "$"))
		return (CHAR_DOLLAR);
	else if (!strcmp(value, "("))
		return (CHAR_BRACKET_O);
	else if (!strcmp(value, ")"))
		return (CHAR_BRACKET_C);
	else
		return (WORD);
}

void	lexer_advance(t_lexer *lexer)
{
	lexer->pos++;
	if ((unsigned int)lexer->pos < strlen(lexer->input))
		lexer->cur_char = lexer->input[lexer->pos];
	else
		lexer->cur_char = '\0';
}

int	is_string_identify(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| ((c >= '0' && c <= '9') || c == '_'));
}

t_tok	*lexer_identifier(t_lexer *lexer)
{
	int		start_pos;
	char	*ident;
	t_tok	*token;

	start_pos = lexer->pos;
	while (is_string_identify(lexer->cur_char)
		|| lexer->cur_char == '.' || lexer->cur_char == '\'')
		lexer_advance(lexer);
	ident = ft_strndup(lexer->input + start_pos, lexer->pos - start_pos);
	token = create_token(ident, WORD);
	return (token);
}

t_tok	*lexer_pipe(t_lexer *lexer)
{
	t_tok	*token;

	token = create_token("|", CHAR_PIPE);
	lexer_advance(lexer);
	return (token);
}
