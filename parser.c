/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/18 15:37:20 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void parse_command(t_parser *parser, t_cmd_node **cmd_list, t_env *env)
{
	int cmd_flag = 1;
	t_cmd_node *current_node = NULL;
	t_cmd *current_cmd = NULL;

	if (!parser || !cmd_list)
	{
		perror("parser or cmd_list is NULL");
		return ;
	}
	while (parser->current_token != NULL)
	{
		if (cmd_flag == 1)
		{
			t_cmd_node *new_node = calloc(1, sizeof(t_cmd_node));
			if (new_node == NULL)
			{
				perror("Failed to allocate memory for cmd_node");
				free_cmd_list(*cmd_list);
				return ;
			}
			if (*cmd_list == NULL)
				*cmd_list = new_node;
			else
			{
				if (current_node != NULL)
					current_node->next = new_node;
			}
			current_node = new_node;
			current_node->cmd = calloc(1, sizeof(t_cmd));
			if (current_node->cmd == NULL)
			{
				perror("Failed to allocate memory for cmd");
				free_cmd_list(*cmd_list);
				return ;
			}
			current_cmd = current_node->cmd;
			cmd_flag = 0;
		}
		if (parser->current_token->type == CHAR_PIPE)
		{
			current_cmd->pipe = true;
			cmd_flag = 1;
		}
		else if (parser->current_token->type == CHAR_MORE || parser->current_token->type == CHAR_DOUBLE_MORE) // Output redirection
		{
			if (parser->current_token->type == 256)
				current_cmd->fd_append = true;
			parser_advance(parser);
			if (parser->current_token->type == WORD)
			{
				current_cmd->fd_out = strdup(parser->current_token->value);
				if (current_cmd->fd_out == NULL)
				{
					perror("Failed to duplicate output redirection path");
					free_cmd_list(*cmd_list);
					return;
				}
			}
		}
		else if (parser->current_token->type == CHAR_LESS)
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
						return;
					}
				}
			}
		}
		else if (parser->current_token->type == WORD)
		{
			if (current_cmd->command == NULL)
			{
				current_cmd->command = strdup(parser->current_token->value);
				if (current_cmd->command == NULL)
				{
					perror("Failed to duplicate command string");
					free_cmd_list(*cmd_list);
					return ;
				}
				current_cmd->args = calloc(2, sizeof(char*));
				if (current_cmd->args == NULL)
				{
					perror("Failed to allocate memory for args");
					free_cmd_list(*cmd_list);
					return ;
				}
				current_cmd->args[0] = current_cmd->command;
			}
			else
			{
				int args_len;
				for (args_len = 0; current_cmd->args[args_len] != NULL; ++args_len);
				char **new_args = realloc(current_cmd->args, sizeof(char*) * (args_len + 2));
				if (new_args == NULL) {
					perror("Failed to reallocate memory for args");
					free_cmd_list(*cmd_list);
					return ;
				}
				current_cmd->args = new_args;
				current_cmd->args[args_len] = strdup(parser->current_token->value);
				if (current_cmd->args[args_len] == NULL)
				{
					perror("Failed to duplicate argument string");
					free_cmd_list(*cmd_list);
					return ;
				}
				current_cmd->args[args_len + 1] = NULL;
			}
		}
		parser_advance(parser);
	}
	char **envp = env_to_char_array(env);
	ft_execute(*cmd_list, env);
	free_char_array(envp);
}
