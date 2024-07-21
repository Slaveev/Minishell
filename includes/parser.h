/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:50:42 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 15:51:59 by dslaveev         ###   ########.fr       */
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

typedef struct s_manager
{
	t_cmd_node	**cmd_list;
	t_cmd_node	**current_node;
	t_cmd		**current_cmd;
}				t_manager;

void		parse(t_parser *parser, t_cmd *cmd, char **env);
void		parse_command(t_parser *parser, t_cmd_node **cmd_list, t_env *env);
void		parser_advance(t_parser *parser);
t_parser	*init_parser(t_lexer *lexer);
int			is_builtin(char *command);
bool		heredoc_check(t_parser *parser, t_cmd *cmd);

t_cmd_node	*create_cmd_node(void);
void initialize_cmd_node(t_parser *parser, t_manager *cmd_mgmt, int *cmd_flag);
// void		initialize_cmd_node(t_parser *parser, t_cmd_node **cmd_list,
// 				t_cmd_node **current_node, t_cmd **current_cmd, int *cmd_flag);
void		handle_pipe(t_cmd *current_cmd, int *cmd_flag);
void		handle_output_redirection(t_parser *parser, t_cmd *current_cmd,
				t_cmd_node **cmd_list);
void		handle_input_redirection(t_parser *parser, t_cmd *current_cmd,
				t_cmd_node **cmd_list);

#endif
