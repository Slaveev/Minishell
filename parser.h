/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:50:42 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/13 11:07:58 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_tok	*current_token;
}			t_parser;

void		parse(t_parser *parser);
void		parse_command(t_parser *parser);
void		parser_advance(t_parser *parser);
t_parser	*init_parser(t_lexer *lexer);

#endif
