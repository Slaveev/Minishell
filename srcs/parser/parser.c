/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 14:28:31 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	initialize_cmd_node(t_parser *parser, t_cmd_node **cmd_list, t_cmd_node **current_node, t_cmd **current_cmd, int *cmd_flag)
{
	t_cmd_node	*new_node;

	new_node = calloc(1, sizeof(t_cmd_node));
	(void)parser;
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
		if (*current_node != NULL)
			(*current_node)->next = new_node;
	}
	*current_node = new_node;
	(*current_node)->cmd = calloc(1, sizeof(t_cmd));
	if ((*current_node)->cmd == NULL)
	{
		perror("Failed to allocate memory for cmd");
		free_cmd_list(*cmd_list);
		return ;
	}
	*current_cmd = (*current_node)->cmd;
	*cmd_flag = 0;
}

void	handle_pipe(t_cmd *current_cmd, int *cmd_flag)
{
	current_cmd->pipe = true;
	*cmd_flag = 1;
}

void	handle_output_redirection(t_parser *parser, t_cmd *current_cmd, t_cmd_node **cmd_list)
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

void	handle_input_redirection(t_parser *parser, t_cmd *current_cmd, t_cmd_node **cmd_list)
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

void	handle_command_and_args(t_parser *parser, t_cmd *current_cmd, t_cmd_node **cmd_list)
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
		current_cmd->args = calloc(2, sizeof(char *));
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
		if (new_args == NULL)
		{
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

void	parse_command(t_parser *parser, t_cmd_node **cmd_list, t_env *env)
{
	int			cmd_flag;
	t_cmd_node	*current_node;
	t_cmd		*current_cmd;
	char		**envp;

	cmd_flag = 1;
	current_node = NULL;
	current_cmd = NULL;
	while (parser->current_token != NULL)
	{
		if (cmd_flag == 1)
			initialize_cmd_node(parser, cmd_list, &current_node, &current_cmd, &cmd_flag);
		switch (parser->current_token->type)
		{
			case CHAR_PIPE:
				handle_pipe(current_cmd, &cmd_flag);
				break ;
			case CHAR_MORE:
			case CHAR_DOUBLE_MORE:
				handle_output_redirection(parser, current_cmd, cmd_list);
				break ;
			case CHAR_LESS:
				handle_input_redirection(parser, current_cmd, cmd_list);
				break ;
			case WORD:
				handle_command_and_args(parser, current_cmd, cmd_list);
				break ;
		}
		parser_advance(parser);
	}
	envp = env_to_char_array(env);
	ft_execute(*cmd_list, env);
	free_char_array(envp);
}

// if (!parser || !cmd_list) {
//     perror("parser or cmd_list is NULL");
//     return;
// }

// void parse_command(t_parser *parser, t_cmd_node **cmd_list, t_env *env)
// {
// 	int cmd_flag = 1;
// 	t_cmd_node *current_node = NULL;
// 	t_cmd *current_cmd = NULL;

// 	while (parser->current_token != NULL)
// 	{
// 		if (cmd_flag == 1)
// 		{
// 			t_cmd_node *new_node = calloc(1, sizeof(t_cmd_node));
// 			if (new_node == NULL)
// 			{
// 				perror("Failed to allocate memory for cmd_node");
// 				free_cmd_list(*cmd_list);
// 				return ;
// 			}
// 			if (*cmd_list == NULL)
// 				*cmd_list = new_node;
// 			else
// 			{
// 				if (current_node != NULL)
// 					current_node->next = new_node;
// 			}
// 			current_node = new_node;
// 			current_node->cmd = calloc(1, sizeof(t_cmd));
// 			if (current_node->cmd == NULL)
// 			{
// 				perror("Failed to allocate memory for cmd");
// 				free_cmd_list(*cmd_list);
// 				return ;
// 			}
// 			current_cmd = current_node->cmd;
// 			cmd_flag = 0;
// 		}
// 		if (parser->current_token->type == CHAR_PIPE)
// 		{
// 			current_cmd->pipe = true;
// 			cmd_flag = 1;
// 		}
// 		else if (parser->current_token->type == CHAR_MORE || parser->current_token->type == CHAR_DOUBLE_MORE) // Output redirection
// 		{
// 			if (parser->current_token->type == 256)
// 				current_cmd->fd_append = true;
// 			parser_advance(parser);
// 			if (parser->current_token->type == WORD)
// 			{
// 				current_cmd->fd_out = strdup(parser->current_token->value);
// 				if (current_cmd->fd_out == NULL)
// 				{
// 					perror("Failed to duplicate output redirection path");
// 					free_cmd_list(*cmd_list);
// 					return;
// 				}
// 			}
// 		}
// 		else if (parser->current_token->type == CHAR_LESS)
// 		{
// 			if (heredoc_check(parser, current_cmd))
// 			{
// 				parser_advance(parser);
// 				current_cmd->fd_heredoc = strdup(parser->current_token->value);
// 			}
// 			else
// 			{
// 				parser_advance(parser);
// 				if (parser->current_token->type == WORD)
// 				{
// 					current_cmd->fd_in = strdup(parser->current_token->value);
// 					if (current_cmd->fd_in == NULL)
// 					{
// 						perror("Failed to duplicate input redirection path");
// 						free_cmd_list(*cmd_list);
// 						return;
// 					}
// 				}
// 			}
// 		}
// 		else if (parser->current_token->type == WORD)
// 		{
// 			if (current_cmd->command == NULL)
// 			{
// 				current_cmd->command = strdup(parser->current_token->value);
// 				if (current_cmd->command == NULL)
// 				{
// 					perror("Failed to duplicate command string");
// 					free_cmd_list(*cmd_list);
// 					return ;
// 				}
// 				current_cmd->args = calloc(2, sizeof(char*));
// 				if (current_cmd->args == NULL)
// 				{
// 					perror("Failed to allocate memory for args");
// 					free_cmd_list(*cmd_list);
// 					return ;
// 				}
// 				current_cmd->args[0] = current_cmd->command;
// 			}
// 			else
// 			{
// 				int args_len;
// 				for (args_len = 0; current_cmd->args[args_len] != NULL; ++args_len);
// 				char **new_args = realloc(current_cmd->args, sizeof(char*) * (args_len + 2));
// 				if (new_args == NULL) {
// 					perror("Failed to reallocate memory for args");
// 					free_cmd_list(*cmd_list);
// 					return ;
// 				}
// 				current_cmd->args = new_args;
// 				current_cmd->args[args_len] = strdup(parser->current_token->value);
// 				if (current_cmd->args[args_len] == NULL)
// 				{
// 					perror("Failed to duplicate argument string");
// 					free_cmd_list(*cmd_list);
// 					return ;
// 				}
// 				current_cmd->args[args_len + 1] = NULL;
// 			}
// 		}
// 		parser_advance(parser);
// 	}
// 	char **envp = env_to_char_array(env);
// 	ft_execute(*cmd_list, env);
// 	free_char_array(envp);
// }
