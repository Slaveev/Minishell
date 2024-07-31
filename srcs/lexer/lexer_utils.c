/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:13:47 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/31 13:58:25 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../libft/libft.h"

char *strip_single_quotes(char *str)
{
    int i;

    i = ft_strlen(str);
    if (str[0] == '\'' && str[i - 1] == '\'')
    {
        str[i - 1] = '\0';
        return (str + 1);
    }
    return (str);
}


char	*strip_quotes(char *str)
{
	int	i;

	i = ft_strlen(str);
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
	ident = ft_strndup(lexer->input + start_pos, lexer->pos - start_pos);
	token = create_token(ident, WORD);
	free(ident);
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
	word = ft_strndup(lexer->input + start_pos, lexer->pos - start_pos);
	token = create_token(word, WORD);
	free(word);
	return (token);
}

t_tok	*process_token(t_lexer *lexer, char end_char, int token_type,
					int quotes)
{
	int		start_pos;
	char	*ident;
	t_tok	*token;
	int		flag;

	flag = 0;
	lexer_advance(lexer);
	start_pos = lexer->pos;
	while (lexer->cur_char != end_char && lexer->cur_char != '\0')
		lexer_advance(lexer);
	ident = ft_strndup(lexer->input + start_pos, lexer->pos - start_pos);
	if (quotes == 1)
	{
		ident = strip_single_quotes(ident);
		flag = 1;
	}
	else if (quotes == 2)
		ident = strip_quotes(ident);
	token = create_token(ident, token_type);
	token->flag = flag;
	lexer_advance(lexer);
	free(ident);
	return (token);
}
