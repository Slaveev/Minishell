/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:43:25 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/22 11:21:46 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_cmd_node	*create_cmd_node(void)
{
	t_cmd_node	*node;

	node = calloc(1, sizeof(t_cmd_node));
	if (node)
	{
		node->cmd = calloc(1, sizeof(t_cmd));
		if (!node->cmd)
		{
			free(node);
			node = NULL;
		}
	}
	return (node);
}

void	initialize_cmd_node(t_parser *parser, t_manager *cmd_mng, int *cmd_flag)
{
	t_cmd_node	*new_node;

	(void)parser;
	new_node = create_cmd_node();
	if (new_node == NULL)
	{
		perror("Failed to allocate memory for cmd_node");
		if (cmd_mng->cmd_list)
			free_cmd_list(*(cmd_mng->cmd_list));
		return ;
	}
	if (*(cmd_mng->cmd_list) == NULL)
		*(cmd_mng->cmd_list) = new_node;
	else if (*(cmd_mng->current_node) != NULL)
		(*(cmd_mng->current_node))->next = new_node;
	*(cmd_mng->current_node) = new_node;
	*(cmd_mng->current_cmd) = new_node->cmd;
	*cmd_flag = 0;
}

void	handle_pipe(t_cmd *current_cmd, int *cmd_flag)
{
	current_cmd->pipe = true;
	*cmd_flag = 1;
}

void	handle_output_redirection(t_parser *parser, t_cmd *current_cmd,
		t_cmd_node **cmd_list)
{
	if (parser->current_token->type == CHAR_DOUBLE_MORE)
		current_cmd->fd_append = true;
	parser_advance(parser);
	if (parser->current_token->type == WORD)
	{
		current_cmd->fd_out = strdup(parser->current_token->value);
		if (current_cmd->fd_out == NULL)
		{
			perror("Failed to duplicate output redirection path");
			free_cmd_list(*cmd_list);
			return ;
		}
	}
}

void	handle_input_redirection(t_parser *parser, t_cmd *current_cmd,
		t_cmd_node **cmd_list)
{
	if (heredoc_check(parser, current_cmd))
	{
		parser_advance(parser);
		current_cmd->fd_heredoc = strdup(parser->current_token->value);
	}
	else
	{
		parser_advance(parser);
		if (parser->current_token->type == WORD)
		{
			current_cmd->fd_in = strdup(parser->current_token->value);
			if (current_cmd->fd_in == NULL)
			{
				perror("Failed to duplicate input redirection path");
				free_cmd_list(*cmd_list);
				return ;
			}
		}
	}
}
