/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:50:42 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/18 15:15:17 by dslaveev         ###   ########.fr       */
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

void		parse(t_parser *parser, t_cmd *cmd, char **env);
void		parse_command(t_parser *parser, t_cmd_node **cmd_list, t_env *env);
void		parser_advance(t_parser *parser);
t_parser	*init_parser(t_lexer *lexer);
int			is_builtin(char *command);
bool		heredoc_check(t_parser *parser, t_cmd *cmd);

#endif
