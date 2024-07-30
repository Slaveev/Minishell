/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:12:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 14:37:26 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../libft/libft.h"

int	get_token_type(char *value)
{
	if (!ft_strcmp(value, "<"))
		return (CHAR_LESS);
	else if (!ft_strcmp(value, ">"))
		return (CHAR_MORE);
	else if (!ft_strcmp(value, ">>"))
		return (CHAR_DOUBLE_MORE);
	else if (!ft_strcmp(value, "|"))
		return (CHAR_PIPE);
	else if (!ft_strcmp(value, " "))
		return (CHAR_SPACE);
	else if (!ft_strcmp(value, "\'"))
		return (CHAR_QUOTE);
	else if (!ft_strcmp(value, "\""))
		return (CHAR_DOUBLE_QUOTE);
	else if (!ft_strcmp(value, "\\"))
		return (CHAR_BACKSLASH);
	else if (!ft_strcmp(value, "$"))
		return (CHAR_DOLLAR);
	else if (!ft_strcmp(value, "("))
		return (CHAR_BRACKET_O);
	else if (!ft_strcmp(value, ")"))
		return (CHAR_BRACKET_C);
	else
		return (WORD);
}

void	lexer_advance(t_lexer *lexer)
{
	lexer->pos++;
	if ((unsigned int)lexer->pos < ft_strlen(lexer->input))
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
	free(ident);
	return (token);
}

t_tok	*lexer_pipe(t_lexer *lexer)
{
	t_tok	*token;

	token = create_token("|", CHAR_PIPE);
	lexer_advance(lexer);
	return (token);
}
