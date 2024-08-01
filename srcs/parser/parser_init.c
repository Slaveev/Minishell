/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:35:43 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/31 15:00:00 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	return (parser);
}

void	parser_advance(t_parser *parser)
{
	if (parser->current_token != NULL)
		destroy_token(parser->current_token);
	parser->current_token = lexer_get_next_token(parser->lexer);
}

int	process_tokens(t_parser *parser, t_manager *cmd_mgmt, int *cmd_flag)
{
	int	flag;

	flag = 0;
	while (parser->current_token != NULL)
	{
		if (*cmd_flag == 1)
			initialize_cmd_node(parser, cmd_mgmt, cmd_flag);
		if (parser->current_token->type == CHAR_PIPE)
			handle_pipe(*(cmd_mgmt->current_cmd), cmd_flag);
		else if (parser->current_token->type == CHAR_MORE
			|| parser->current_token->type == CHAR_DOUBLE_MORE)
			handle_output_redirection(parser, *(cmd_mgmt->current_cmd),
				cmd_mgmt->cmd_list);
		else if (parser->current_token->type == CHAR_LESS)
			handle_input_redirection(parser, *(cmd_mgmt->current_cmd),
				cmd_mgmt->cmd_list);
		else if (parser->current_token->type == WORD)
			flag = (handle_command_and_args(parser, *(cmd_mgmt->current_cmd),
						cmd_mgmt->cmd_list));
		parser_advance(parser);
	}
	return (flag);
}
